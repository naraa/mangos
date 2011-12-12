-- Areatrigger table format change

ALTER TABLE `areatrigger_teleport`
    CHANGE `required_quest_done` `required_quest_done_A` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Alliance quest",
    CHANGE `required_quest_done_heroic` `required_quest_done_heroic_A` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Alliance heroic quest",
    ADD COLUMN `required_quest_done_H` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Horde quest" AFTER `required_quest_done_A`,
    ADD COLUMN `required_quest_done_heroic_H` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Horde heroic quest" AFTER `required_quest_done_heroic_A`,
    ADD COLUMN `minGS` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Min player gear score",
    ADD COLUMN `maxGS` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Max player gear score",
    ADD COLUMN `achiev_id_0` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Required achievement to enter in heroic difficulty",
    ADD COLUMN `achiev_id_1` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Required achievement to enter in extra difficulty",
    ADD COLUMN `combat_mode` int(11) UNSIGNED NOT NULL DEFAULT "0" COMMENT "Possibility for enter while zone in combat";

UPDATE `areatrigger_teleport` SET `required_quest_done_H`=`required_quest_done_A` WHERE `required_quest_done_A` > 0;
UPDATE `areatrigger_teleport` SET `required_quest_done_heroic_H`=`required_quest_done_heroic_A` WHERE `required_quest_done_heroic_A` > 0;

-- Areatrigger additional data
UPDATE `areatrigger_teleport` SET `achiev_id_0` = 4530, `achiev_id_1` = 4597 WHERE `target_map` = 631;

-- UPDATE `areatrigger_teleport` SET `combat_mode` = 1 WHERE `target_map` = 631;

UPDATE `areatrigger_teleport` SET `minGS` = 192 WHERE `target_map` > 600;

