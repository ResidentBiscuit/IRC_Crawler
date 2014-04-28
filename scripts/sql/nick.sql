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
