-- Run this script through the SQL client to create the tables of the database --
	-- NOTE, this file is very important. Do not make changes to this unless you are certain you know --
	-- exactly what you are doing. It is used when building the database. --

-- Creates the irc_network table --

CREATE TABLE irc_network(
	network_id 		serial 			NOT NULL,
	network_name	varchar(50)		NOT NULL UNIQUE,
	user_count		bigint			NULL,
	PRIMARY KEY(network_id)
	);
	
-- Create the channel table --

CREATE TABLE channel(
	channel_id		serial			NOT NULL,
	network_id		int				NOT NULL,
	channel_name	varchar(100)	NOT NULL,
	motd			varchar(200)	NULL,
	title			varchar(50)		NULL,
	user_count		int				NULL,
	PRIMARY KEY(channel_id),
	FOREIGN KEY(network_id)
					REFERENCES irc_network(network_id)
						ON UPDATE NO ACTION
						ON DELETE NO ACTION
	);
	
-- Creates channel_mode table --

CREATE TABLE channel_mode(
	channel_id		int		NOT NULL,
	channel_mode	char(1)	NOT NULL,
	PRIMARY KEY(channel_id, channel_mode),
	FOREIGN KEY(channel_id)
					REFERENCES channel(channel_id)
						ON UPDATE NO ACTION
						ON DELETE NO ACTION
	);

-- Create nick table --

CREATE TABLE nick(
	nick_id		serial		NOT NULL,
	nick		varchar(50)	NOT NULL UNIQUE,
	network_id	int			NOT NULL,
	PRIMARY KEY(nick_id),
	FOREIGN KEY(network_id)
		REFERENCES irc_network(network_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION
	);
		
-- Creates chan_nick_intersection table --

CREATE TABLE chan_nick_intersection(
	nick_id		int		NOT NULL,
	channel_id	int		NOT NULL,
	times_seen	int		NULL,
	PRIMARY KEY(nick_id, channel_id),
	FOREIGN KEY(nick_id)
		REFERENCES nick(nick_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION,
	FOREIGN KEY(channel_id)
		REFERENCES channel(channel_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION
	);
	
-- Creates nick_mode table --

CREATE TABLE nick_mode(
	nick_id		int		NOT NULL,
	channel_id	int		NOT NULL,
	mode		char(1)	NOT NULL,
	PRIMARY KEY(nick_id, channel_id, mode),
	FOREIGN KEY(nick_id)
		REFERENCES nick(nick_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION,
	FOREIGN KEY(channel_id)
		REFERENCES channel(channel_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION
	);
	
-- Creates user_name table --

CREATE TABLE user_name(
	user_id		serial			NOT NULL,
	network_id	int				NOT NULL,
	user_name	varchar(100)	NOT NULL,
	real_name	varchar(100) 	NULL,
	PRIMARY KEY(user_id),
	FOREIGN KEY(network_id)
		REFERENCES irc_network(network_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION
	);
	
-- Create the country table --

CREATE TABLE country(
	country_code	char(2)			NOT NULL,
	country_name	varchar(100)	NOT NULL UNIQUE,
	subnet			cidr			NOT NULL,
	CONSTRAINT		country_key		PRIMARY KEY(country_code)
	);
	
-- Creates user_nick_intersection table --

CREATE TABLE user_nick_intersection(
	user_id		int		NOT NULL,
	nick_id		int		NOT NULL,
	network_id	int		NOT NULL,
	ip_addr		inet	NULL,
	hostname	varchar(100)	NULL,
	country_code	char(2)		NULL,
	PRIMARY KEY(user_id,nick_id,network_id),
	FOREIGN KEY(user_id)
		REFERENCES user_name(user_id)
			ON UPDATE NO ACTION
			ON DELETE NO ACTION,
	FOREIGN KEY(nick_id)
			REFERENCES nick(nick_id)
				ON UPDATE NO ACTION
				ON DELETE NO ACTION,
	FOREIGN KEY(network_id)
			REFERENCES irc_network(network_id)
				ON UPDATE NO ACTION
				ON DELETE NO ACTION,
	FOREIGN KEY(country_code)
			REFERENCES country(country_code)
				ON UPDATE NO ACTION
				ON DELETE NO ACTION
	);
	
-- Creates message table --

CREATE TABLE message(
	user_id		int				NOT NULL,
	nick_id		int				NOT NULL,
	network_id	int				NOT NULL,
	time_stamp	timestamp		NOT NULL,
	message		varchar(250)	NOT NULL,
	recipient	varchar(100)	NOT NULL,
	PRIMARY KEY(user_id, nick_id, network_id, time_stamp),
	FOREIGN KEY(user_id) 	REFERENCES user_name(user_id),
	FOREIGN KEY(nick_id) 	REFERENCES nick(nick_id),
	FOREIGN KEY(network_id)	REFERENCES irc_network(network_id)
	);			
