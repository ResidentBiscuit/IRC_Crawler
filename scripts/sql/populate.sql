-- This file populates all tables of the irc_crawler_test database with some testing data.
-- Some of these INSERTS will FAIL, due to some constraints. This is what should happen, we're testing here :)
-- DO NOT RUN THIS ON A PRODUCTION DATATBASE --

INSERT INTO irc_network(network_name, user_count) VALUES('irc.freenode.net', 0);
INSERT INTO irc_network(network_name, user_count) VALUES('irc.quakenet.org', 0);
INSERT INTO irc_network(network_name, user_count) VALUES('irc.rizon.net', 0);
INSERT INTO irc_network(network_name, user_count) VALUES('irc.snoonet.org', 0);
INSERT INTO irc_network(network_name, user_count) VALUES('irc.efnet.org', 0);

INSERT INTO channel(network_id, channel_name, title, motd, modes, user_count) VALUES(1, '#freenode', 'This is a title', 'Heres a message of the day', '+asdf', 0);
INSERT INTO channel(network_id, channel_name, title, motd, modes, user_count) VALUES(1, '#C++', 'This is C++', 'We write code', '+sdif', 0);
INSERT INTO channel(network_id, channel_name, title, motd, modes, user_count) VALUES(2, '#database', 'Anything database related', 'Latest postgresql version out!', '+zxcv', 0);
INSERT INTO channel(network_id, channel_name, title, motd, modes, user_count) VALUES(1, '#postgresql', 'PostgreSQL!', 'Official support', '+sdif', 0);
INSERT INTO channel(network_id, channel_name, title, motd, modes, user_count) VALUES(5, '#java', 'Java questions', 'Java sucks...', '+tyui', 0);

INSERT INTO nick(network_id, nick, ip_address) VALUES(1, 'residentbiscuit', '8.8.8.8');
INSERT INTO nick(network_id, nick) VALUES(1, 'jready');
INSERT INTO nick(network_id, nick) VALUES(1, 'jared');
INSERT INTO nick(network_id, nick) VALUES(1, 'jd');
INSERT INTO nick(network_id, nick) VALUES(2, 'residentbiscuit');

INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(1, 1);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(2, 1);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(3, 1);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(4, 1);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(1, 2);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(2, 3);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(5, 4);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(3, 3);
INSERT INTO channel_nick_intersection(nick_id, channel_id) VALUES(1, 3);

INSERT INTO message(nick_id, message, recipient) VALUES(1, 'yolo swag', '#postgresql');
INSERT INTO message(nick_id, message, recipient) VALUES(1, 'hello world', '#database');
INSERT INTO message(nick_id, message, recipient) VALUES(1, 'testing 1 2', '#postgresql');
INSERT INTO message(nick_id, message, recipient) VALUES(2, 'maybe I should watch game of thrones', '#postgresql');
INSERT INTO message(nick_id, message, recipient) VALUES(2, 'how do postgres', '#postgresql');
INSERT INTO message(nick_id, message, recipient) VALUES(3, 'Why use smart pointers', '#C++');
INSERT INTO message(nick_id, message, recipient) VALUES(1, 'Because they make life easy', '#C++');
INSERT INTO message(nick_id, message, recipient) VALUES(3, 'Oh', '#C++');
INSERT INTO message(nick_id, message, recipient) VALUES(4, 'asdf', '#freenode');
INSERT INTO message(nick_id, message, recipient) VALUES(4, 'hey guys', '#database');
INSERT INTO message(nick_id, message, recipient) VALUES(2, 'yeah postgres so cool', '#postgresql');
INSERT INTO message(nick_id, message, recipient) VALUES(2, 'too cool', '#postgresql');
INSERT INTO message(nick_id, message, recipient) VALUES(3, 'isnt beethoven just awesome?', '#freenode');
INSERT INTO message(nick_id, message, recipient) VALUES(1, 'beethoven is so swag', '#freenode');
