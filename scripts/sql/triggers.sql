-- Run this script through the SQL client to create the triggers for the database. --

-- Trigger for keeping channel.user_count up to date
-- Note, PRE-RI_... in place because this trigger must run before FK constraint,
-- and FK constraints are all RI_...
CREATE TRIGGER "PRE_RI_update_channel_user_count"
	AFTER INSERT OR DELETE ON channel_nick_intersection
	FOR EACH ROW
	EXECUTE PROCEDURE update_channel_user_count();

-- This trigger makes sure that a nick does not join a channel outside of its network
CREATE TRIGGER verify_networks
	AFTER INSERT ON channel_nick_intersection
	FOR EACH ROW
	EXECUTE PROCEDURE verify_networks();