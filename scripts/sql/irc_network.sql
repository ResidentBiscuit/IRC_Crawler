-- Creates the IRC_NETWORK table --

CREATE TABLE irc_network(
	network_id 		serial 			NOT NULL,
	network_name	varchar(50)		NOT NULL UNIQUE,
	user_count		bigint			NULL,
	PRIMARY KEY(network_id)
	);
