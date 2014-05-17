-- This script handles the creation of the various views on the database. Each database table has a view created that the application
-- will actually interact with. For the most part, application code should only hit views, and not physical tables.

-- Creates view in front irc_network
CREATE VIEW network_view AS
SELECT network_name, user_count
FROM irc_network;

-- Create messages view: Displays columns (message_id, network, recipient, nick, message, timestamp)
CREATE VIEW messages AS
SELECT  m.message_id, net.network_name, m.recipient, n.nick, m.message, m.time
FROM    message m
    JOIN nick n ON m.nick_id = n.nick_id
    JOIN irc_network net ON n.network_id = net.network_id;