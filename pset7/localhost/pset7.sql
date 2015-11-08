-- MySQL dump 10.13  Distrib 5.5.32, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `transaction_log`
--

DROP TABLE IF EXISTS `transaction_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transaction_log` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `transaction_type` char(1) NOT NULL,
  `symbol` varchar(15) NOT NULL,
  `amount` int(10) NOT NULL,
  `price` decimal(65,4) unsigned NOT NULL,
  `datetime_stamp` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction_log`
--

LOCK TABLES `transaction_log` WRITE;
/*!40000 ALTER TABLE `transaction_log` DISABLE KEYS */;
INSERT INTO `transaction_log` VALUES (5,13,'B','FB',5,51.9554,'2013-10-17 20:19:17'),(6,13,'B','GOOG',3,887.5400,'2013-10-17 20:19:25'),(7,13,'B','TSLA',8,182.3700,'2013-10-17 20:19:35'),(8,13,'S','FB',5,51.9554,'2013-10-17 20:19:47'),(9,13,'S','GOOG',3,887.5400,'2013-10-17 20:19:56'),(10,13,'B','TSLA',1,182.4320,'2013-10-17 20:20:13'),(11,13,'S','TSLA',8,182.3700,'2013-10-17 20:20:19'),(12,13,'B','TSLA',3,182.3400,'2013-10-17 20:20:27'),(13,13,'S','TSLA',3,182.3400,'2013-10-17 20:20:44');
/*!40000 ALTER TABLE `transaction_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_stocks`
--

DROP TABLE IF EXISTS `user_stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_stocks` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `transaction_timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `symbol` varchar(15) NOT NULL,
  `company` varchar(255) NOT NULL,
  `stock_exchange` varchar(255) NOT NULL,
  `shares_amount` int(10) unsigned NOT NULL,
  `share_price` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_id` (`user_id`,`transaction_timestamp`)
) ENGINE=InnoDB AUTO_INCREMENT=26 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_stocks`
--

LOCK TABLES `user_stocks` WRITE;
/*!40000 ALTER TABLE `user_stocks` DISABLE KEYS */;
INSERT INTO `user_stocks` VALUES (22,13,'2013-10-17 18:19:25','GOOG','Google Inc.','Google Inc.',2,887.5400),(24,13,'2013-10-17 18:20:13','TSLA','Tesla Motors, Inc','Tesla Motors, Inc',1,182.4320),(25,13,'2013-10-17 18:20:27','TSLA','Tesla Motors, Inc','Tesla Motors, Inc',2,182.3400);
/*!40000 ALTER TABLE `user_stocks` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`jharvard`@`localhost`*/ /*!50003 TRIGGER `new_stock_row_insert_transaction_log` AFTER INSERT ON `user_stocks`
 FOR EACH ROW INSERT INTO transaction_log (user_id, symbol, transaction_type, amount, price, datetime_stamp) VALUES (NEW.user_id, NEW.symbol, 'B', NEW.shares_amount, NEW.share_price, now()) */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`jharvard`@`localhost`*/ /*!50003 TRIGGER `update_transaction_log` AFTER UPDATE ON `user_stocks` FOR EACH ROW BEGIN
    IF (new.shares_amount > old.shares_amount) THEN
        INSERT INTO transaction_log (user_id, symbol, transaction_type, amount, price, datetime_stamp) VALUES (new.user_id, new.symbol, 'B', old.shares_amount, new.share_price, now());
    ELSEIF (new.shares_amount < old.shares_amount) THEN
        INSERT INTO transaction_log (user_id, symbol, transaction_type, amount, price, datetime_stamp) VALUES (new.user_id, new.symbol, 'S', old.shares_amount, new.share_price, now());
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'cs50','$1$50$ceNa7BV5AoVQqilACNLuC1',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'nate','$1$50$sUyTaTbiSKVPZCpjJckan0',10000.0000),(6,'rbowden','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(7,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',10000.0000),(8,'tmacwilliam','$1$50$91ya4AroFPepdLpiX.bdP1',10000.0000),(9,'zamyla','$1$50$Suq.MOtQj51maavfKvFsW1',10000.0000),(13,'edward','$1$nJ3FNMS5$tRv7sDVfH5Qz8zppjpRcT.',8678.5470);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-10-17 20:26:28
