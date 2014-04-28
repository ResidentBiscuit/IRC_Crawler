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
