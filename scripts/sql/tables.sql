-- Run this script through the SQL client to create the tables of the database --
	-- NOTE, this file is very important. Do not make changes to this unless you are certain you know --
	-- exactly what you are doing. It is used when building the database. --

-- Creates the irc_network table --
CREATE TABLE irc_network(
	network_id		serial			NOT NULL,
	network_name	varchar(256)	NOT NULL UNIQUE,
	user_count		integer			NULL,
	PRIMARY KEY(network_id)
	);
	
-- Creates the channel table --
CREATE TABLE channel(
	channel_id		serial			NOT NULL,
	network_id		integer			NOT NULL,
	channel_name	varchar(256)	NOT NULL,
	title			varchar(256)	NULL,
	motd			varchar(2048)	NULL,
	user_count		integer			NULL,
	modes			varchar(256)	NULL,
	PRIMARY KEY(channel_id),
	UNIQUE(channel_name, network_id),
	FOREIGN KEY(network_id)	REFERENCES irc_network(network_id)
	);
	
-- Creates the country table --
CREATE TABLE country(
	country_code	char(2)			NOT NULL,
	country			varchar(2048)	NOT NULL UNIQUE,
	subnet			inet			NOT NULL,
	PRIMARY KEY(country_code)
	);
	
-- Creates the nick table --
CREATE TABLE nick(
	nick_id			serial			NOT NULL,
	nick			varchar(256)	NOT NULL,
	network_id		integer			NOT NULL,
	country_code	char(2)			NULL,
	ip_address		inet			NULL,
	hostname		varchar(512)	NULL,
	PRIMARY KEY(nick_id),
	FOREIGN KEY(network_id)		REFERENCES irc_network(network_id),
	FOREIGN KEY(country_code)	REFERENCES country(country_code),
	UNIQUE(nick, network_id)
	);
	
-- Creates the channel_nick_intersection table --
CREATE TABLE channel_nick_intersection(
	channel_id		integer			NOT NULL,
	nick_id			integer			NOT NULL,
	times_seen		integer			NULL,
	modes			varchar(256)	NULL,
	PRIMARY KEY(channel_id, nick_id),
	FOREIGN KEY(channel_id) REFERENCES channel(channel_id),
	FOREIGN KEY(nick_id)	REFERENCES nick(nick_id)
	);
	
-- Creates the message table --
CREATE TABLE message(
	message_id		serial			NOT NULL,
	nick_id			integer			NOT NULL,
	message			varchar(4096)	NOT NULL,
	recipient		varchar(512)	NOT NULL,
	time			timestamp		NOT NULL DEFAULT now(),
	PRIMARY KEY(message_id),
	FOREIGN KEY(nick_id)	REFERENCES nick(nick_id)
	);
