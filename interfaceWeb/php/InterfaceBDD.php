<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of InterfaceBDD
 *
 * @author kev29lt
 */
require_once('consts.php');
require_once('Utilisateur.php');
require_once('Theme.php');
require_once('Partie.php');

class InterfaceBDD {

    private $bdd;

    public function InterfaceBDD() {
        $this->Connect();
    }

    public function getBdd() {
        return $this->bdd;
    }

    public function setBdd($_bdd) {
        $this->bdd = $_bdd;
    }

    public function Connect() {
        try {
            $this->setBdd(new PDO('mysql:host=' . DB_SERVER . ';dbname=' . DB_NAME . ';charset=utf8', DB_USER, DB_PASSWORD));
        } catch (PDOException $exception) {
            error_log('Connection error: ' . $exception->getMessage());
            return false;
        }
        return $this->getBdd();
    }

    public function AddUser($user) {
        try {
            $request = 'insert into Utilisateur(mail, prenom, nom, mdp)
            values(:mail, :prenom, :nom, :mdp)';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':mail', $user->getMail(), PDO::PARAM_STR, 256);
            $statement->bindParam(':prenom', $user->getPrenom(), PDO::PARAM_STR, 128);
            $statement->bindParam(':nom', $user->getNom(), PDO::PARAM_STR, 128);
            $statement->bindParam(':mdp', $user->getMdp(), PDO::PARAM_STR, 128);
            $result = $statement->execute();
        } catch (PDOException $exception) {
            error_log('Connection error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RequestUser($id) {
        try {
            $request = 'select * from Utilisateur where id_utilisateur=:id';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':id', $id, PDO::PARAM_INT);
            $statement->execute();
            $result = $statement->fetchAll(PDO::FETCH_CLASS, 'Utilisateur');
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function UpdateUser($user) {
        try {
            $request = 'update Utilisateur mail=:mail, prenom=:prenom, nom=:nom, mdp=:mdp where set id_utilisateur=:id';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':id', $user->getId_utilisateur(), PDO::PARAM_INT);
            $statement->bindParam(':mail', $user->getMail(), PDO::PARAM_STR, 256);
            $statement->bindParam(':prenom', $user->getPrenom(), PDO::PARAM_STR, 128);
            $statement->bindParam(':nom', $user->getNom(), PDO::PARAM_STR, 128);
            $statement->bindParam(':mdp', $user->getMdp(), PDO::PARAM_STR, 128);
            $result = $statement->execute();
        } catch (PDOException $exception) {
            error_log('Connection error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RemoveUser($id) {
        try {
            $request = 'delete from Utilisateur where id_utilisateur=:id';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':id', $id, PDO::PARAM_INT);
            $result = $statement->execute();
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RequestTheme($id) {
        try {
            $request = 'select * from Theme where id_theme=:id';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':id', $id, PDO::PARAM_INT);
            $statement->execute();
            $result = $statement->fetchAll(PDO::FETCH_CLASS, 'Theme');
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RequestAllThemes() {
        try {
            $request = 'select * from Theme';
            $statement = $this->getBdd()->prepare($request);
            $statement->execute();
            $result = $statement->fetchAll(PDO::FETCH_CLASS, 'Theme');
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function AddPartie($partie) {
        try {
            $request = 'insert into Partie(nom_partie) values(:nom_partie)';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':nom_partie', $partie->getNom_partie(), PDO::PARAM_STR, 256);
            $result = $statement->execute();
        } catch (PDOException $exception) {
            error_log('Connection error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RequestPartie($id) {
        try {
            $request = 'select * from Partie where id_partie=:id';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':id', $id, PDO::PARAM_INT);
            $statement->execute();
            $result = $statement->fetchAll(PDO::FETCH_CLASS, 'Partie');
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RequestAllParties() {
        try {
            $request = 'select * from Partie';
            $statement = $this->getBdd()->prepare($request);
            $statement->execute();
            $result = $statement->fetchAll(PDO::FETCH_CLASS, 'Partie');
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

    public function RemovePartie($id) {
        try {
            $request = 'delete from Partie where id_partie=:id';
            $statement = $this->getBdd()->prepare($request);
            $statement->bindParam(':id', $id, PDO::PARAM_INT);
            $result = $statement->execute();
        } catch (PDOException $exception) {
            error_log('Request error: ' . $exception->getMessage());
            return false;
        }
        return $result;
    }

}
