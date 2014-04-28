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
