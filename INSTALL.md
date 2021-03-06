# Projet CIR2 ISEN Brest/Rennes BurgerQuiz 2018

Le Projet BurgerQuiz comporte deux parties, l'outil d'administration et le site Web.

# Déployement

## Téléchargement

Deux solutions sont possibles pour télécharger le projet :

* Vous pouvez cloner le Git officiel du projet, en utilisant la commande suivante (en supposant que l'utilitaire Git est installé sur votre machine) : 
``` 
git clone https://github.com/BlivionIaG/burgerquiz.git
```
* Vous pouvez télécharger le projet au lien suivant : ![ICI](https://github.com/BlivionIaG/burgerquiz/archive/master.zip) puis le dézipper dans le dossier de votre choix
```
unzip master.zip
```

## Dépendances

### Outil administration système
Pour compiler le projet vous aurez besoin de QT5 et MySQL Connector C++ et de G++
* Pour les installer sous Debian (et autres dérivés) :
```
sudo apt-get install qt5-default libmysqlcppconn-dev build-essential
```
* Après avoir installé MySQL Connector C++, modifiez la configuration de MySQL :
```
nano /etc/mysql/mariadb.conf.d/50-server.cnf
```
* Commentez la ligne ```"bind-address = 127.0.0.1"```
* Redémmarez MySQL :
```
sudo service mysql restart
```
 ou 
```
sudo systemctl restart mysql
```

### Site Web
Le site web fonctionne avec PHP7 et MySQL (Oracle ou MariaDB)
* Pour les installer sous Debian (et autres dérivés) :
```
sudo apt-get install apache2 mysql-server php7.0 libapache2-mod-php7.0 php7.0-gd php7.0-mysql php7.0-bz2 php7.0-json php7.0-curl php7.0-intl php7.0-mcrypt php-mbstring php7.0-mbstring phpmyadmin
```
* (facultatif) Après d'avoir installé MySQL, pour changer le mot de passe root exécutez :
```
sudo mysql_secure_installation
```

## Installation

### La Base de donnée
Pour installer la base, ouvrez MySQL dans la racine du projet :
```
mysql -u root -p
```
* ou si vous n'avez pas mis de mot de passe
```
mysql -u root
```
* Puis chargez le script SQL contenu dans le dossier interfaceWeb/
```
source interfaceWeb/burgerquiz.sql;
```
Remarque : Si une base du même nom existe, elle sera remplacée, de même dans le cas des tables
* Ensuite, ouvrez votre naavigateur et allez sur ![localhost/phpmyadmin](127.0.0.1/phpmyadmin)
Connectez vous, Cliquez sur "Burgerquiz" ( ou le nom de la base ), puis allez dans l'onglet "Privilèges".
Ensuite cliquez sur "Add New User", Remplissez le champ "User name", "Password" et "Re-type"
puis descendez en bas de la page pour cliquer sur "GO"
* Pour finir, il faut modifier le fichier consts.php dans interfaceWeb/php/consts.php
```
  define('DB_USER', 'NOM_UTILISATEUR');
  define('DB_PASSWORD', 'MOT_DE_PASSE_UTILISATEUR');
  define('DB_NAME', 'NOM_BASE_DE_DONNE');
  define('DB_SERVER', 'ADDRESSE_SERVEUR');
```

### Le Site Web
Pour installer le site web, c'est simple il suffit de copier le contenu de interfaceWeb dans votre dossier sur lequel votre virtualhost pointe.

### L'outil administration système
Allez dans interfaceCpp/burger/
Pour compiler :
```
qmake
make
```
Vous pouvez maintenant executer:
```
./burger
```