-- Define functions --

-- This function should only be called whenever an entry is added/removed from the channel_nick_intersection table
-- It increments/decrements the user_count of channels and irc_networks whenever a user joins/leaves a channel
CREATE FUNCTION update_user_count() RETURNS TRIGGER AS $$
DECLARE
    _inc integer;
    _channel_id integer;
    
BEGIN
    IF tg_op = 'INSERT' THEN
        _inc := 1;
        _channel_id := NEW.channel_id;
    ELSIF tg_op = 'DELETE' THEN
        _inc := -1;
        _channel_id := OLD.channel_id;
    ELSE
        raise exception 'Unexpected Operation %', tg_op;
    END IF;
    
    UPDATE channel SET user_count = channel.user_count + _inc WHERE channel.channel_id = _channel_id;
    IF NOT FOUND THEN
        raise exception 'channel_id % not found', _channel_id;
    END IF;

    RETURN NULL;
END $$ LANGUAGE plpgsql;


-- This function is called when anything is inserted into channel_nick_intersection, that both the channel's
-- and the nick's networks match up 
CREATE OR REPLACE FUNCTION verify_networks_match(nick_id integer, channel_id integer) RETURNS BOOLEAN AS $$
    BEGIN
        RETURN (SELECT(n.network_id = c.network_id)
            FROM nick n
            LEFT JOIN channel c ON c.channel_id = $2
            WHERE n.nick_id = $1);
    END;
$$ LANGUAGE plpgsql;