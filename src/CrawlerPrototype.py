import socket
import sys
import re
 
# Prototype for the IRC_Crawler (need a real name :) )
 
server = "irc.freenode.net"
channel = "#botwar"
nick = "ResidentCrawler"
user = "jready"
 
irc_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
irc_socket.connect((server, 6667))
irc_socket.send("NICK " + nick + "\r\nUSER " + user + " 0 * :" + nick + "\r\n")
irc_socket.send("JOIN " + channel + "\r\n")
 
joined = 0
channel_list = []
while joined == 0:
	recv_text = irc_socket.recv(1024)
	sys.stdout.write(recv_text)
	# Handle server PINGs
	if recv_text.find("PING"):
		irc_socket.send("PONG " + recv_text.split()[1] + "\r\n")
 
	# If this text is seen, then we should have joined the channel...
	# There's probably a better way of doing this
	if str.find(recv_text, "ResidentCrawler " + channel) != -1:
		joined = 1
		# Get list of public channels from the network
		irc_socket.send("LIST\r\n")
		while recv_text.find("End of /LIST") == -1:
			recv_text = irc_socket.recv(1024)
			channel_regex = re.compile(r"([#&][^\s]{0,200})")
			if channel_regex.search(recv_text) != None:
				channel_list.append(channel_regex.search(recv_text).group(0))
	
 
 
	for channel in channel_list:
		print channel
		

