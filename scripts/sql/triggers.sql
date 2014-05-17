-- Run this script through the SQL client to create the triggers for the database. --

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
END $$ language plpgsql;

-- Trigger for keeping channel.user_count up to date
-- Note, PRE-RI_... in place because this trigger must run before FK constraint,
-- and FK constraints are all RI_...
CREATE TRIGGER "PRE_RI_update_user_count"
	AFTER INSERT OR DELETE ON channel_nick_intersection
	FOR EACH ROW
	EXECUTE PROCEDURE update_user_count();
