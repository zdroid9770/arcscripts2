DELETE FROM `ai_agents` WHERE `entry`=6206;
INSERT INTO `ai_agents` (`entry`, `instance_mode`, `type`, `event`, `chance`, `maxcount`, `spell`, `spelltype`, `targettype_overwrite`, `cooldown_overwrite`, `floatMisc1`, `Misc2`) VALUES 
(6206, 0, 4, 2, 100, 0, 7405, 11, 1, 35000, 0, 0),
(6206, 0, 4, 0, 100, 1, 7164, 10, 4, 0, 0, 0),
(6206, 0, 3, 2, 100, 0, 0, 0, -1, -1, 0.2, 10000);
