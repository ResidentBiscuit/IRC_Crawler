-- This file contains various queries which may be useful --

-- Returns all messages in all #postgresql channels --
SELECT	recipient, message, time
FROM	message
WHERE	recipient = '#postgresql';

-- Returns all messages with their recipients said by residentbiscuit --
SELECT	nick.nick_id, nick.nick, message.message, message.recipient, message.time
FROM	message
INNER JOIN nick
ON		message.nick_id = nick.nick_id
WHERE	nick.nick = 'residentbiscuit';

-- Returns channels and thier networks and orders based on number of users, in descending order --
SELECT	irc_network.network_name, channel.channel_name, channel.user_count
FROM	channel
INNER JOIN irc_network
ON		channel.network_id = irc_network.network_id
ORDER BY user_count DESC;
