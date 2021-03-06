<?php
/*
 * Copyright (C) 2018 Kévin Le Torc'h <Kévin at kev29lt@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file play.php
 * \brief Jeu du site
 * \author Kévin Le Torc'h <Kévin at kev29lt@gmail.com>
 * \version 1.2
 * \date 13 juin 2018
 */
define('ENVIRONMENT', 't');
session_start();

if (isset($_SESSION)) {
    if ($_SESSION['isConnected'] == false) {
        header('Location: index.php');
    }
}

$id_partie = filter_input(INPUT_GET, 'partie', FILTER_SANITIZE_NUMBER_INT);
if (!isset($id_partie) && $id_partie <= 0) {
    header('Location: parties.php');
}
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <meta name="description" content="Jouer Partie">
        <meta name="author" content="Kévin Le Torc'h et Antoine Orhant">

        <!-- Bootstrap core CSS-->
        <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
        <!-- Custom fonts for this template-->
        <link href="vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
        <!-- Page level plugin CSS-->
        <link href="vendor/datatables/dataTables.bootstrap4.css" rel="stylesheet">
        <!-- Custom styles for this template-->
        <link href="vendor/fonts.googleapis/bubblegum-sans.css" rel="stylesheet">

        <link href="css/general.css" rel="stylesheet" type="text/css">
        <link href="css/notify.css" rel="stylesheet" type="text/css">
    </head>
    <body>
        <?php require_once("includes/nav.template.php"); ?>
        <input type="hidden" id="bq-id_partie" value=<?php echo '"' . $id_partie . '"' ?>>

        <div id="bq-play" class="container-fluid base-main-content bq-game">
            <div>
                <button id="startGame" class="bq-button">Commencer</button>
            </div>
            <div id="bq-proposition">

            </div>
            <div id="bq-reponses">

            </div>
            <div id="bq-progress-bar">

            </div>
        </div>

        <audio id="bq-win-sound" src="mp3/win.mp3"></audio>
        <audio id="bq-good-sound" src="mp3/good.mp3"></audio>   
        <audio id="bq-bad-sound" src="mp3/bad.mp3"></audio>
        <audio id="bq-alarm-sound" src="mp3/alarm.mp3"></audio>

        <div id="bq-timer" class="bq-circle"></div>

        <?php require_once("includes/footer.template.php"); ?>       

        <script src="vendor/jquery/jquery.slim.min.js"></script>
        <script src="js/ajax.js"></script>
        <script src="js/game.js"></script>
        <script src="js/notify.js"></script>

        <?php
        $notifyTitle = filter_input(INPUT_GET, 'notifyTitle', FILTER_SANITIZE_STRING);
        $notifyContent = filter_input(INPUT_GET, 'notifyContent', FILTER_SANITIZE_STRING);
        $notifyType = filter_input(INPUT_GET, 'notifyType', FILTER_SANITIZE_STRING);
        $notifyTime = filter_input(INPUT_GET, 'notifyTime', FILTER_SANITIZE_NUMBER_INT);

        if (isset($notifyContent)) {
            $notifyContent = urldecode($notifyContent);
        } else {
            $notifyContent = '';
        }

        if (!isset($notifyType)) {
            $notifyType = 'info';
        }

        if (!isset($notifyTime)) {
            $notifyTime = 10000;
        }

        if (isset($notifyTitle)) {
            echo '<script> new NotifyNotification("' . urldecode($notifyTitle) . '","' . $notifyContent . '","' . $notifyType . '");</script>';
        }
        ?>
    </body>
</html>
