<%@ Page Language="C#" AutoEventWireup="true" CodeFile="wEBpAGEpROJET3.aspx.cs" Inherits="Projet3" %>

<!DOCTYPE html>
<html>
<title>W3.CSS</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link href="font-awesome-4.7.0/css/font-awesome.min.css" rel="stylesheet" />
<link href="StyleSheet3.css" rel="stylesheet" />
<link href="StyleSheet2.css" rel="stylesheet" />
<style>
body, h1,h2,h3,h4,h5,h6 {font-family: "Century Gothic", sans-serif}
.w3-row-padding img {margin-bottom: 12px}
/* Set the width of the sidebar to 120px */
.w3-sidebar {width: 120px;background: #222;}
/* Add a left margin to the "page content" that matches the width of the sidebar (120px) */
#main {margin-left: 120px}
/* Remove margins from "page content" on small screens */
@media only screen and (max-width: 600px) {#main {margin-left: 0}}
</style>
<body class="w3-black">

<!-- Icon Bar (Sidebar - hidden on small screens) -->
<nav class="w3-sidebar w3-bar-block w3-small w3-hide-small w3-center">
  <!-- Avatar image in top left corner -->
  <img src="/w3images/avatar_smoke.jpg" style="width:100%">
  <a href="#" class="w3-bar-item w3-button w3-padding-large w3-black">
    <i class="fa fa-home w3-xxlarge"></i>
    <p>PRÉSENTATION</p>
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
    <a href="#" class="w3-bar-item w3-button" style="width:25% !important">HOME</a>
    <a href="#users" class="w3-bar-item w3-button" style="width:25% !important">USERS</a>
    <a href="#maps" class="w3-bar-item w3-button" style="width:25% !important">MAPS</a>
    <a href="#achievements" class="w3-bar-item w3-button" style="width:25% !important">ACHIEVEMENTS</a>
    <a href="#connect" class="w3-bar-item w3-button" style="width:25% !important">CONNECT</a>
  </div>
</div>

<!-- Page Content -->
<div class="w3-padding-large" id="main">
  <!-- Header/Home -->
  <header class="w3-container w3-padding-32 w3-center w3-black" id="home">
    <h1 class="w3-jumbo"> Projet Intégrateur 3</h1>
    <p>LOG3900: Projet d'évolution d'un logiciel. Polytechnique de Montréal</p>
  </header>

  <!-- Presentation Section -->
  <div class="w3-content w3-justify w3-text-grey w3-padding-64">
    <h2 class="w3-text-light-grey">Notre Projet</h2>
    <hr style="width:200px" class="w3-opacity">
    <p>Le simulateur de robot réalisé dans le cadre du cours INF2990 constitue la base du produit demandé dans 
       le cadre de cet appel d’offres. Le présent projet est une extension de ce simulateur dont l’objectif principal 
       est d’ajouter deux nouvelles fonctionnalités : la possibilité d’éditer simultanément en  réseau,  ainsi  que 
       l’édition de zone de simulation à partir d’un iPad.
    </p>
    <h3 class="w3-padding-16 w3-text-light-grey">Notre Équipe</h3>
    <p class="w3-wide">Olivier St-Amour</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:95%"></div>
    </div>
    <p class="w3-wide">Camille Gendreau</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:85%"></div>
    </div>
    <p class="w3-wide">Simon-Pierre Desjardins</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:80%"></div>
    </div><br>
    <p class="w3-wide">Frédéric Grégoire</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:55%"></div>
    </div>
    <p class="w3-wide">Philippe Marcotte</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:15%"></div>
    </div>
    <p class="w3-wide">Ulric Villeneuve</p>
    <div class="w3-white">
      <div class="w3-dark-grey" style="height:28px;width:85%"></div>
    </div><br>
    
    <div class="w3-row w3-center w3-padding-16 w3-section w3-light-grey">
      <div class="w3-quarter w3-section">
        <span class="w3-xlarge">11+</span><br>
        Partners
      </div>
      <div class="w3-quarter w3-section">
        <span class="w3-xlarge">55+</span><br>
        Projects Done
      </div>
      <div class="w3-quarter w3-section">
        <span class="w3-xlarge">89+</span><br>
        Happy Clients
      </div>
      <div class="w3-quarter w3-section">
        <span class="w3-xlarge">150+</span><br>
        Meetings
      </div>
    </div>
  </div>
  <!-- End Presentation Section -->

  <!-- Users Section -->
  <div class="w3-padding-64 w3-content" id="users">
    <h2 class="w3-text-light-grey">Utilisateurs sur le server</h2>
    <hr style="width:200px" class="w3-opacity">

  </div>
  <!-- End Users Section -->
  
  <!-- Map Section -->
  <div class="w3-padding-64 w3-content" id="maps">
    <h2 class="w3-text-light-grey">Cartes sur le server</h2>
    <hr style="width:200px" class="w3-opacity">

    <!-- Grid for maps on the server -->
    <div class="w3-row-padding" style="margin:0 -16px">
      <div class="w3-half w3-margin-bottom">
        <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
          <li class="w3-dark-grey w3-xlarge w3-padding-32">Nom de la carte #1</li>
          <li class="w3-padding-16">Nombre de poteaux: 0</li>
          <li class="w3-padding-16">Nombre de murs: 0</li>
          <li class="w3-padding-16">Nombre de lignes: 0</li>
          <li class="w3-padding-16">Nombre de joueurs: 0</li>
          <li class="w3-padding-16">Mode: Édition</li>
        </ul>
      </div>

      <div class="w3-half">
        <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
          <li class="w3-dark-grey w3-xlarge w3-padding-32">Nom de la carte #2</li>
          <li class="w3-padding-16">Nombre de poteaux: 0</li>
          <li class="w3-padding-16">Nombre de murs: 0</li>
          <li class="w3-padding-16">Nombre de lignes: 0</li>
          <li class="w3-padding-16">Nombre de joueurs: 0</li>
          <li class="w3-padding-16">Mode: Édition</li>
        </ul>
      </div>
    </div>
    <!-- End Grid for maps on the server -->

  </div>
  <!-- End Map Section -->

  <!-- Achievement Section -->
  <div class="w3-padding-64 w3-content" id="achievements">
    <h2 class="w3-text-light-grey">Liste d'accomplissements possible</h2>
    <hr style="width:200px" class="w3-opacity">

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
      </div>

      <!-- Online time achivements -->
      <h3 class="w3-padding-16 w3-text-light-grey">Temps en ligne</h3>
      <div class="w3-row-padding" style="margin: 0 -16px">
          <div class="w3-half w3-margin-bottom">
              <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                  <li class="w3-dark-grey w3-xlarge w3-padding-32">Débutant en ligne</li>
                  <li class="w3-padding-16">
                      L'utilisateur à passé un minimum de 60 minutes en ligne sur son
                      profils.
                  </li>
              </ul>
          </div>

          <div class="w3-half">
              <ul class="w3-ul w3-white w3-center w3-opacity w3-hover-opacity-off">
                  <li class="w3-dark-grey w3-xlarge w3-padding-32">Connaisseur en ligne</li>
                  <li class="w3-padding-16">
                      L'utilisateur à passé un minimum de 600 minutes en ligne sur son
                      profils.
                  </li>
              </ul>
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
                  <li class="w3-padding-16">
                      L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                      profils.
                  </li>
              </ul>
          </div>

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
                      <li class="w3-padding-16">
                          L'utilisateur à passé un minimum de 6000 minutes en ligne sur son
                          profils.
                      </li>
                  </ul>
              </div>
          </div>
      </div>
      <!-- End Grid for possible achievements -->

      </div>
          <!-- End Achievement Section -->

          <!-- Connect Section -->
          <div class="w3-padding-64 w3-content w3-text-grey" id="connect">
              <h2 class="w3-text-light-grey">S'authentifier au serveur</h2>
              <hr style="width: 200px" class="w3-opacity">

              <div class="w3-section">
                  <p><i class="fa fa-map-marker fa-fw w3-text-white w3-xxlarge w3-margin-right"></i>Chicago, US</p>
                  <p><i class="fa fa-phone fa-fw w3-text-white w3-xxlarge w3-margin-right"></i>Phone: +00 151515</p>
                  <p><i class="fa fa-envelope fa-fw w3-text-white w3-xxlarge w3-margin-right"></i>Email: mail@mail.com</p>
              </div>
              <br>
              <p>Lets get in touch. Send me a message:</p>

              <form action="/action_page.php" target="_blank">
                  <p>
                      <input class="w3-input w3-padding-16" type="text" placeholder="Name" required name="Name"></p>
                  <p>
                      <input class="w3-input w3-padding-16" type="text" placeholder="Email" required name="Email"></p>
                  <p>
                      <input class="w3-input w3-padding-16" type="text" placeholder="Subject" required name="Subject"></p>
                  <p>
                      <input class="w3-input w3-padding-16" type="text" placeholder="Message" required name="Message"></p>
                  <p>
                      <button class="w3-button w3-padding-large" type="submit">
                          <i class="fa fa-paper-plane"></i>SEND MESSAGE
                      </button>
                  </p>
              </form>
          </div>
          <!-- End Connect Section -->

          <!-- Footer -->
          <footer class="w3-content w3-padding-64 w3-text-grey w3-xlarge">
              <i class="fa fa-facebook-official w3-hover-text-indigo"></i>
              <i class="fa fa-instagram w3-hover-text-purple"></i>
              <i class="fa fa-snapchat w3-hover-text-yellow"></i>
              <i class="fa fa-pinterest-p w3-hover-text-red"></i>
              <i class="fa fa-twitter w3-hover-text-light-blue"></i>
              <i class="fa fa-linkedin w3-hover-text-indigo"></i>
              <p class="w3-medium">Powered by <a href="https://www.w3schools.com/w3css/default.asp" target="_blank" class="w3-hover-text-green">w3.css</a></p>
              <!-- End footer -->
          </footer>

          <!-- END PAGE CONTENT -->
      </div>

</body>
</html>
