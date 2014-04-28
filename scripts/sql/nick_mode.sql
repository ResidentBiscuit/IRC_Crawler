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
