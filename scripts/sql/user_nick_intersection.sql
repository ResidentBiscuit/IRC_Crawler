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

