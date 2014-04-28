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
