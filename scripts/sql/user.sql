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
