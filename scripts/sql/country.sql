-- Create the country table --

CREATE TABLE country(
	country_code	char(2)			NOT NULL,
	country_name	varchar(100)	NOT NULL UNIQUE,
	subnet			cidr			NOT NULL,
	CONSTRAINT		country_key		PRIMARY KEY(country_code)
	);
