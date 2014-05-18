-- This script handles the creation of the various views on the database. Each database table has a view created that the application
-- will actually interact with. For the most part, application code should only hit views, and not physical tables.

-- Creates view in front irc_network
CREATE VIEW networks_view AS
SELECT network_name, user_count
FROM irc_network;

-- Creates view in front of channel
CREATE VIEW channels_view AS
SELECT n.network_name, c.channel_name, c.title, c.motd, c.user_count, c.modes
FROM channel c
    INNER JOIN irc_network n ON c.network_id = n.network_id;

-- Creates view in front of nick
CREATE VIEW nicks_view AS
SELECT n.network_name, nick.nick, c.country, nick.ip_address, nick.hostname
FROM nick nick
    INNER JOIN irc_network n ON n.network_id = nick.network_id
    LEFT JOIN country c ON c.country_code = nick.country_code;

-- Creates view in front of channel_nick_intersection
CREATE VIEW nicks_channels_view AS
SELECT net.network_name, c.channel_name, n.nick, cn.times_seen, cn.modes
FROM channel_nick_intersection cn
    INNER JOIN channel c ON c.channel_id = cn.channel_id
    INNER JOIN irc_network net ON net.network_id = c.network_id
    INNER JOIN nick n ON n.nick_id = cn.nick_id;

-- Create messages view: Displays columns (message_id, network, recipient, nick, message, timestamp)
CREATE VIEW messages_view AS
SELECT  m.message_id, net.network_name, m.recipient, n.nick, m.message, m.time
FROM    message m
    JOIN nick n ON m.nick_id = n.nick_id
    JOIN irc_network net ON n.network_id = net.network_id;