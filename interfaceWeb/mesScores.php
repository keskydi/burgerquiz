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
 * \file mesScores.php
 * \brief Menu des scores de l'utilisateur
 * \author Kévin Le Torc'h <Kévin at kev29lt@gmail.com>
 * \version 1.1
 * \date 11 juin 2018
 */
define('ENVIRONMENT', 't');

require_once('php/InterfaceBDD.php');
session_start();

if (isset($_SESSION)) {
    if ($_SESSION['isConnected'] == false) {
        header('Location: index.php');
    }

    if (isset($_SESSION['user'])) {
        $user = new Utilisateur();
        $user->fromArray($_SESSION['user']);
    }
}
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        <meta name="description" content="Mes Scores">
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

        <div class="container-fluid base-main-content">
            <h1 align="center" id="bq-info-page"> Mes Scores </h1>
            <input class="form-control mr-sm-2" id="bq-searchbar" type="text" placeholder="Search..." aria-label="Search">
            <table id="bq-searchtab" class="bq-table">
                <tr>
                    <th> Partie </th>
                    <th> Thème </th>
                    <th> Score </th>
                    <th> Temps </th>
                </tr>
                <?php /* Liste des scores de l'utilisateur */
                if (isset($user)) {
                    $db = new InterfaceBDD();
                    $messcores = $db->GetScores($user->getId_utilisateur());

                    foreach ($messcores as $monscore) {
                        $montheme = $db->GetTheme($monscore['id_partie']);

                        echo '<tr>';
                        echo '<td>' . $monscore['nom_partie'] . '</td>';
                        echo '<td>' . $montheme['nom_theme'] . '</td>';
                        echo '<td>' . $monscore['score'] . '</td>';
                        echo '<td>' . $monscore['temps'] . '</td>';
                        echo '</tr>';
                    }
                }
                ?>
            </table>
            <button id="bq-fixed-retour" onclick="location.href = 'palmares.php';"> Retour </button>
        </div>

        <?php require_once("includes/footer.template.php"); ?>

        <!-- Appel des Scripts -->
        <script src="vendor/jquery/jquery.slim.min.js"></script>
        <script src="vendor/bootstrap/js/bootstrap.min.js"></script>   
        <script src="js/searchbar.js"></script>
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