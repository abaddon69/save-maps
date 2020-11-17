/*
 Navicat Premium Data Transfer

 Source Server         : 10.0.1.38_3306
 Source Server Type    : MySQL
 Source Server Version : 50634
 Source Host           : 10.0.1.38:3306
 Source Schema         : player

 Target Server Type    : MySQL
 Target Server Version : 50634
 File Encoding         : 65001

 Date: 22/01/2019 17:10:07
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for save_teleport
-- ----------------------------
DROP TABLE IF EXISTS `save_teleport`;
CREATE TABLE `save_teleport`  (
  `id` int(11) NOT NULL,
  `name` varchar(32) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `pos` tinyint(3) NOT NULL,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `map_index` int(11) NOT NULL,
  PRIMARY KEY (`id`, `pos`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Compact;

SET FOREIGN_KEY_CHECKS = 1;
