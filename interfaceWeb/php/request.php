<?php

require_once('InterfaceBDD.php');

function sendJsonData($message, $h) {
    header($h);
    header('Content-Type: text/plain; charset=utf-8');
    header('Cache-control: no-store, no-cache, must-revalidate');
    header('Pragma: no-cache');
    echo json_encode($message);
}

$db = new InterfaceBDD();

if (!$db->getBdd()) {
    header('HTTP/1.1 503 Service Unavailable');
    exit;
}

$requestMethod = $_SERVER['REQUEST_METHOD'];
$tmp = substr($_SERVER['PATH_INFO'], 1);
$request = explode('/', $tmp);
$requestRessource = array_shift($request);

if ($requestRessource === 'startGame') {
    if ($requestMethod === 'POST') {
        $id = filter_input(INPUT_POST, 'id', FILTER_SANITIZE_NUMBER_INT);

        if (isset($id)) {
            $tmpquiz = $db->RequestGameReadyQuestions($id);
            $quiz = [];
            foreach ($tmpquiz as $elem) {
                array_push($quiz, array(
                    'proposition' => $elem['proposition'],
                    'choix_un' => $elem['choix_un'],
                    'choix_deux' => $elem['choix_deux'],
                    'valeur_reponse' => $elem['valeur_reponse']
                        )
                );
            }

            $_SESSION['quiz'] = $quiz;
            $_SESSION['cursor'] = 0;
            $_SESSION['gameScore'] = [];

            array_push($_SESSION['gameScore'], array(0, time(), -1, -1));

            $tmpout = $_SESSION['quiz'][$_SESSION['cursor']];
            $output = array(
                'progress' => 100 * $_SESSION['cursor'] / sizeof($_SESSION['quiz']),
                'proposition' => $tmpout['proposition'],
                'choix_un' => $tmpout['choix_un'],
                'choix_deux' => $tmpout['choix_deux']
            );

            sendJsonData($output, 'HTTP/1.1 200 OK'); // On envoie le résultat
        }
    }
} else {
    header('HTTP/1.1 400 Bad Request');
}

exit;
?>