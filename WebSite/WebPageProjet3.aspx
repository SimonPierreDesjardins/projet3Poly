﻿<!-- 
 @file   WebPageProjet3.aspx
 @author Frédéric Grégoire
 @date   2017-03-16   
-->
<%@ Page Language="C#" AutoEventWireup="true" CodeFile="wEBpAGEpROJET3.aspx.cs" Inherits="Projet3" %>


<!DOCTYPE html>
<html>
    <head>
        <title>Fred's webpage</title>
        <link rel="shortcut icon" href="Icons/halfLife.ico" />
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="font-awesome-4.7.0/css/font-awesome.min.css" rel="stylesheet" />
        <link href="w3.css" rel="stylesheet" />
        <link href="StyleSheet.css" rel="stylesheet" />
        <style>
            body, h1, h2, h3, h4, h5, h6 {
                font-family: "Century Gothic", sans-serif;
            }

            .w3-row-padding img {
                margin-bottom: 12px;
            }

            /* Set the width of the sidebar to 120px */
            .w3-sidebar {
                width: 120px;
                background: #222;
            }
            /* Add a left margin to the "page content" that matches the width of the sidebar (120px) */
            #main {
                margin-left: 120px;
            }
            /* Remove margins from "page content" on small screens */
            @media only screen and (max-width: 600px) {
                #main {
                    margin-left: 0;
                }
            }
        </style>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
        <script>
            //Called "onLoad"
            $(document).ready(function () {
                //Dictionary for <mapID, mapName>
                var mapDictionary = {};

                //Load all maps
                $.getJSON("https://api.mlab.com/api/1/databases/projet3/collections/MapInfos?apiKey=6dyiG1KR3iv5bFvxlJDL79N0PC6ijGDx", function (data) {
                    console.log(data);
                    var i;
                    var mapVar;
                    $.each(data, function (i, map) {

                        //Add mapID to mapName in mpaDictionary
                        mapDictionary[map.ID] = map.mapName;

                        //Change map bool privacy to string
                        var mapPrivacy;
                        if (map.isPrivate)
                            mapPrivacy = "Public";
                        else
                            mapPrivacy = "Privée";

                        //Change map int mode to string
                        var mapMode;
                        switch (map.mapType)
                        {
                            case 2:
                                mapMode = "Édition";
                                break;

                            default:
                                mapMode = "Simulation";
                                break;
                        }

                        //Left map
                        if (i % 2 == 0)
                        {
                            mapVar = 'mapBloc' + i.toString();
                            $("#gridOfMaps").append('<div id="' + mapVar + '" class="w3-row-padding" style="margin: 0 -16px">\
                                                          <div class="w3-half w3-margin-bottom">\
                                                              <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">\
                                                                  <li class="w3-dark-grey w3-xlarge w3-padding-32">' + map.mapName + '</li>\
                                                                  <li class="w3-padding-16">Nombre de poteaux: ' + map.nbPoteaux + '</li>\
                                                                  <li class="w3-padding-16">Nombre de murs: ' + map.nbMurs + '</li>\
                                                                  <li class="w3-padding-16">Nombre de lignes: ' + map.nbLignes + '</li>\
                                                                  <li class="w3-padding-16">Confidentialité: ' + mapPrivacy + '</li>\
                                                                  <li class="w3-padding-16">Mode: ' + mapMode + '</li>\
                                                              </ul>\
                                                          </div>');
                        }
                        //Right map
                        else
                        {
                            $("#" + mapVar).append('<div class="w3-half">\
                                                          <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">\
                                                              <li class="w3-dark-grey w3-xlarge w3-padding-32">' + map.mapName + '</li>\
                                                              <li class="w3-padding-16">Nombre de poteaux: ' + map.nbPoteaux + '</li>\
                                                              <li class="w3-padding-16">Nombre de murs: ' + map.nbMurs + '</li>\
                                                              <li class="w3-padding-16">Nombre de lignes: ' + map.nbLignes + '</li>\
                                                              <li class="w3-padding-16">Confidentialité: ' + mapPrivacy + '</li>\
                                                              <li class="w3-padding-16">Mode: ' + mapMode + '</li>\
                                                          </ul>\
                                                      </div>\
                                                  </div>');
                        }
                    });
                    if (i % 2 == 0)
                    {
                        $("#gridOfMaps").append('</div>');
                    }
                });

                //Load all users
                $.getJSON("https://api.mlab.com/api/1/databases/projet3/collections/Users?apiKey=6dyiG1KR3iv5bFvxlJDL79N0PC6ijGDx", function (data) {
                    console.log(data);
                    var i;
                    var userVar;
                    $.each(data, function (i, user) {
                        //Left user
                        if (i % 2 == 0)
                        {
                            userVar = 'userBloc' + i.toString();
                            $("#girdOfUsers").append('<div id="' + userVar + '" class="w3-row-padding" style="margin: 0 -16px">\
                                                          <div class="w3-half w3-margin-bottom">\
                                                              <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">\
                                                                  <li class="w3-dark-grey w3-xlarge w3-padding-32">' + user.Username + '</li>\
                                                                  <li class="w3-padding-16">Cartes modifiées: ' + user.ModifiedMaps + '</li>\
                                                                  <li class="w3-padding-16">Cartes publiées: ' + user.CreatedMaps + '</li>\
                                                                  <li class="w3-padding-16">Nombre de simulations: ' + user.NumberOfSimulations + '</li>\
                                                                  <li class="w3-padding-16">Autre: 0</li>\
                                                              </ul>\
                                                          </div>');
                        }
                        //Right user
                        else
                        {
                            $("#" + userVar).append('<div class="w3-half">\
                                                          <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">\
                                                              <li class="w3-dark-grey w3-xlarge w3-padding-32">' + user.Username + '</li>\
                                                              <li class="w3-padding-16">Cartes modifiées: ' + user.ModifiedMaps + '</li>\
                                                              <li class="w3-padding-16">Cartes publiées: ' + user.CreatedMaps + '</li>\
                                                              <li class="w3-padding-16">Nombre de simulations: ' + user.NumberOfSimulations + '</li>\
                                                              <li class="w3-padding-16">Autre: 0</li>\
                                                          </ul>\
                                                      </div>\
                                                  </div>');
                        }
                    });
                    if (i % 2 == 0)
                    {
                        $("#girdOfUsers").append('</div>');
                    }
                        
                });
                
                
                $("button").click(function () {
                    //Get user input
                    var userName = document.getElementById("connectionUser").value;
                    console.log(userName);
                    //Remove current connected user
                    $("#connectionUser").val('');
                    var foundUser = 0;
                    //Check for user in DataBase
                    $.getJSON("https://api.mlab.com/api/1/databases/projet3/collections/Users?apiKey=6dyiG1KR3iv5bFvxlJDL79N0PC6ijGDx", function (data)
                    {
                        $.each(data, function (i, user)
                        {
                            //Found user in DataBase
                            if (user.Username == userName)
                            {
                                foundUser = 1;
                                $("#connectedUser").text("");
                                $("#connectedUser").append('<div class="w3-row-padding" style="margin: 0 -16px">\
                                                                    <div class="w3-half w3-margin-bottom">\
                                                                        <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">\
                                                                            <li class="w3-green w3-xlarge w3-padding-32">' + user.Username + '</li>\
                                                                            <li class="w3-padding-16">Cartes modifiées: ' + user.ModifiedMaps + '</li>\
                                                                            <li class="w3-padding-16">Cartes publiées: ' + user.CreatedMaps + '</li>\
                                                                            <li class="w3-padding-16">Nombre de simulations: ' + user.NumberOfSimulations + '</li>\
                                                                            <li class="w3-padding-16">Autre: 0</li>\
                                                                        </ul>\
                                                                    </div>\
                                                            </div>');
                            }
                        });
                    });
                    if (!foundUser) {
                        $("#connectedUser").text("");
                        $("#connectedUser").append('<p><font color="red">Cet utilisateur n\'existe pas dans notre base de données</font></p>');
                    }
                });
                
                
            });
        </script>
    </head>
<body class="w3-black">

    <!-- Icon Bar (Sidebar - hidden on small screens) -->
    <nav class="w3-sidebar w3-bar-block w3-small w3-hide-small w3-center">
        <!-- Avatar image in top left corner -->
        <a class="w3-bar-item w3-padding-large">
            <i class="fa w3-xxlarge"></i>
            <br /><br /><br /><br /><br /><br />
        </a>
        <a href="#" class="w3-bar-item w3-button w3-padding-large w3-black">
            <i class="fa fa-home w3-xxlarge"></i>
            <p>PRÉSENTATION</p>
        </a>
        <a href="#team" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
            <i class="fa fa-users w3-xxlarge"></i>
            <p>DÉVELOPPEURS</p>
        </a>
        <a href="#users" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
            <i class="fa fa-user w3-xxlarge"></i>
            <p>UTILISATEURS</p>
        </a>
        <a href="#maps" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
            <i class="fa fa-picture-o w3-xxlarge"></i>
            <p>CARTES</p>
        </a>
        <a href="#achievements" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
            <i class="fa fa-university w3-xxlarge"></i>
            <p>RÉUSSITE</p>
        </a>
        <a href="#connect" class="w3-bar-item w3-button w3-padding-large w3-hover-black">
            <i class="fa fa-check-square-o w3-xxlarge"></i>
            <p>S'AUTHENTIFIER</p>
        </a>
    </nav>

    <!-- Navbar on small screens (Hidden on medium and large screens) -->
    <div class="w3-top w3-hide-large w3-hide-medium" id="myNavbar">
        <div class="w3-bar w3-black w3-opacity w3-hover-opacity-off w3-center w3-small">
            <a href="#" class="w3-bar-item w3-button" style="width: 25% !important">HOME</a>
            <a href="#team" class="w3-bar-item w3-button" style="width: 25% !important">TEAM</a>
            <a href="#users" class="w3-bar-item w3-button" style="width: 25% !important">USERS</a>
            <a href="#maps" class="w3-bar-item w3-button" style="width: 25% !important">MAPS</a>
            <a href="#achievements" class="w3-bar-item w3-button" style="width: 25% !important">ACHIEVEMENTS</a>
            <a href="#connect" class="w3-bar-item w3-button" style="width: 25% !important">CONNECT</a>
        </div>
    </div>

    <!-- Page Content -->
    <div class="w3-padding-large" id="main">
        <!-- Header/Home -->
        <header class="w3-container w3-padding-32 w3-center w3-black" id="home">
            <h1 class="w3-jumbo">Projet Intégrateur 3</h1>
            <!--<button>Get External Content</button>-->
            <p>LOG3900: Projet d'évolution d'un logiciel. Polytechnique de Montréal</p>
            <img src="Pictures/03-GiGL.jpg" alt="boy" class="w3-image" width="950" height="370">
        </header>

        <!-- Presentation Section -->
        <div class="w3-content w3-justify w3-text-light-grey w3-padding-64">
            <h2 class="w3-text-light-grey">Notre Projet</h2>
            <hr style="width: 200px" class="w3-opacity">
            <p>
                Le simulateur de robot réalisé dans le cadre du cours INF2990 constitue la base du produit demandé dans 
                le cadre de cet appel d’offres. Le présent projet est une extension de ce simulateur dont l’objectif principal 
                est d’ajouter deux nouvelles fonctionnalités : la possibilité d’éditer simultanément en  réseau,  ainsi  que 
                l’édition de zone de simulation à partir d’un iPad.
            </p>
        </div>
        <!-- End Presentation Section -->

        <!-- Team members Section -->
        <div class="w3-padding-64 w3-content" id="team">
            <h3 class="w3-padding-16 w3-text-light-grey">Notre Équipe</h3>
            <hr style="width: 200px" class="w3-opacity">

            <h3 class="w3-padding-16 w3-text-light-grey">Serveur</h3>
            <p class="w3-wide">Camille Gendreau</p>
            <p>
                S’occupe majoritairement du serveur et de la base de données, tout en supervisant le bon maintien de l’architecture de 
                notre logiciel. Il a une bonne compréhension de la réseautique et du langage C++.
            </p>

            <h3 class="w3-padding-16 w3-text-light-grey">Client-Lourd</h3>
            <p class="w3-wide">Olivier St-Amour</p>
            <p>
                Possède de bonnes connaissances en C++ et est responsable de la communication entre le client lourd et 
                le serveur. Il s’assure également de la bonne structure de l’architecture tout au long du projet.
            </p>

            <p class="w3-wide">Simon-Pierre Desjardins</p>
            <p>
                Possède  une  bonne  expertise  en  C++  et  sera  responsable  de  travailler  sur l’infrastructure 
                du client lourd. Il est en charge des nouvelles fonctionnalités à intégrer au client lourd.
            </p>

            <p class="w3-wide">Frédéric Grégoire</p>
            <p>
                Responsable de l’interface utilisateur du client lourd ainsi que de la page web. Il a de bonnes connaissances en
                C#, CSS, HTML et JavaScript. Il aura également à travailler sur les sons et le système de sauvegardes.
            </p>

            <h3 class="w3-padding-16 w3-text-light-grey">Client-Léger</h3>
            <p class="w3-wide">Philippe Marcotte</p>
            <p>
                Spécialiste  en  langage  Swift sur iOs.  Il occupe de la communication client et serveur tout en travaillant sur 
                le backend du client-léger et de la cohérence entre les différent client.
            </p>

            <p class="w3-wide">Ulric Villeneuve</p>
            <p>
                Responsable de l’interface utilisateur sur le client-léger ainsi que la migration de notre projet du client lourd 
                vers iOs. Possède une bonne expertise en Swift.
            </p>
        </div>
        <!-- End Team Member Section -->

        <!-- Users Section -->
        <div class="w3-padding-64 w3-content" id="users">
            <h2 class="w3-text-light-grey">Utilisateurs sur le serveur</h2>
            <hr style="width: 200px" class="w3-opacity">

            <div id="girdOfUsers">
            </div>
        </div>
        <!-- End Users Section -->

        <!-- Map Section -->
        <div class="w3-padding-64 w3-content" id="maps">
            <h2 class="w3-text-light-grey">Cartes sur le serveur</h2>
            <hr style="width: 200px" class="w3-opacity">

            <!-- Grid for maps on the server -->
            <div id="gridOfMaps">
            </div>
            <!-- End Grid for maps on the server -->

        </div>
        <!-- End Map Section -->

        <!-- Achievement Section -->
        <div class="w3-padding-64 w3-content" id="achievements">
            <h2 class="w3-text-light-grey">Liste d'accomplissements possible</h2>
            <hr style="width: 200px" class="w3-opacity">

            <!-- Grid for possible achievements -->
            <!-- Colision achivements -->
            <h3 class="w3-padding-16 w3-text-light-grey">Collision</h3>
            <div class="w3-row-padding" style="margin: 0 -16px">
                <div class="w3-half w3-margin-bottom">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Débutant en collision</li>
                        <li class="w3-padding-16">
                            L'utilisateur à effectuer un minimum de 50 collisions avec 
                            n'importe quelle type d'objet présent sur la zone de simulation.
                        </li>
                    </ul>
                </div>

                <div class="w3-half">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Connaisseur en collision</li>
                        <li class="w3-padding-16">
                            L'utilisateur à effectuer un minimum de 500 collisions avec 
                            n'importe quelle type d'objet présent sur la zone de simulation.
                        </li>
                    </ul>
                </div>
            </div>

            <div class="w3-row-padding" style="margin: 0 -16px">
                <div class="w3-half w3-margin-bottom">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Expert en collision</li>
                        <li class="w3-padding-16">
                            L'utilisateur à effectuer un minimum de 5000 collisions avec 
                            n'importe quelle type d'objet présent sur la zone de simulation.
                        </li>
                    </ul>
                </div>
            </div>

            <!-- Online time achivements -->
            <h3 class="w3-padding-16 w3-text-light-grey">Temps en ligne</h3>
            <div class="w3-row-padding" style="margin: 0 -16px">
                <div class="w3-half w3-margin-bottom">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Débutant en ligne</li>
                        <li class="w3-padding-16">L'utilisateur à passé un minimum de 60 minutes en ligne sur son
                      profils.
                        </li>
                    </ul>
                </div>

                <div class="w3-half">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Connaisseur en ligne</li>
                        <li class="w3-padding-16">L'utilisateur à passé un minimum de 600 minutes en ligne sur son
                      profils.
                        </li>
                    </ul>
                </div>
            </div>

            <div class="w3-row-padding" style="margin: 0 -16px">
                <div class="w3-half w3-margin-bottom">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Expert en ligne</li>
                        <li class="w3-padding-16">
                            L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                            profils.
                        </li>
                    </ul>
                </div>
            </div>

            <!-- Create maps achivements -->
            <h3 class="w3-padding-16 w3-text-light-grey">Création de carte</h3>
            <div class="w3-row-padding" style="margin: 0 -16px">
                <div class="w3-half w3-margin-bottom">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Nom de la carte #1</li>
                        <li class="w3-padding-16">
                            L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                            profils.
                        </li>
                    </ul>
                </div>

                <div class="w3-half">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Nom de la carte #2</li>
                        <li class="w3-padding-16">L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                      profils.
                        </li>
                    </ul>
                </div>
            </div>

            <div class="w3-row-padding" style="margin: 0 -16px">
                <div class="w3-half w3-margin-bottom">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Nom de la carte #1</li>
                        <li class="w3-padding-16">L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                        profils.
                        </li>
                    </ul>
                </div>

                <div class="w3-half">
                    <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                        <li class="w3-dark-grey w3-xlarge w3-padding-32">Nom de la carte #2</li>
                        <li class="w3-padding-16">L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                        profils.
                        </li>
                    </ul>
                </div>
            </div>
            <!-- End Grid for possible achievements -->
        </div>
        <!-- End Achievement Section -->

        <!-- Connect Section -->
        <div class="w3-padding-64 w3-content w3-text-white" id="connect">
            <h2 class="w3-text-light-grey">S'authentifier au serveur</h2>
            <hr style="width: 200px" class="w3-opacity">

            <div class="w3-section">
                <p><i class="fa fa-map-marker fa-fw w3-text-white w3-xxlarge w3-margin-right"></i>Université de Montréal, Montréal, Canada</p>
            </div>
            <br>
            <p>Connectez vous au serveur:</p>

            <p>
                <input id="connectionUser" class="w3-input w3-padding-16" type="text" placeholder="Nom d'utilisateur" name="Name">
            </p>
            <p>
                <button class="w3-button w3-padding-large">
                    <i class="fa fa-user-circle-o"></i> Connexion
                </button>
            </p>

            <div id="connectedUser">
            </div>
        </div>
        <!-- End Connect Section -->

        <!-- Footer -->
        <footer class="w3-content w3-padding-64 w3-text-white w3-xlarge">
            <p class="w3-large" style="display:inline"><a href="https://www.facebook.com/" target="_blank"><i class="fa fa-facebook-official w3-hover-text-indigo"></i></a></p>
            <p class="w3-large" style="display:inline"><a href="https://www.instagram.com/?hl=fr" target="_blank"><i class="fa fa-instagram w3-hover-text-purple"></i></a></p>
            <p class="w3-large" style="display:inline"><a href="https://www.snapchat.com" target="_blank"><i class="fa fa-snapchat w3-hover-text-yellow"></i></a></p>
            <p class="w3-large" style="display:inline"><a href="https://www.pinterest.com/" target="_blank"><i class="fa fa-pinterest-p w3-hover-text-red"></i></a></p>
            <p class="w3-large" style="display:inline"><a href="https://twitter.com" target="_blank"><i class="fa fa-twitter w3-hover-text-light-blue"></i></a></p>
            <p class="w3-large" style="display:inline"><a href="https://www.linkedin.com" target="_blank"><i class="fa fa-linkedin w3-hover-text-indigo"></i></a></p>
            
            <p class="w3-medium">Projet crée par la <a href="http://www.polymtl.ca/" target="_blank" class="w3-hover-text-green">Polytechnique de Montréal</a></p>
        </footer>
        <!-- End footer -->

    </div>
    <!-- END PAGE CONTENT -->

</body>
</html>