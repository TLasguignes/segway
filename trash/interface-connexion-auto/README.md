# Connexion automatique

La problématique est la suivante. On souhaite lancer automatiquement une tâche au démarage du systéme. Celle ci aura pour rôle d'attendre qu'un serveur tcp soit à l'écoute sur le port 1337. La tâche connectée, elle lancera un serveur web.
De la même façon, en cas de déconnection ou shutdown du serveur tcp.
Le client (notre tâche) sera déconnecté et fermera le serveur web.

Cette exemple utilise l'interface graphique du segway

## Dossier Test

Attention  ! Le dossier test ne contient que des pseudo tests afin de verifier l'affichage et la reception des donnée avec l'interface graphique (Uniquement lié au Segway).

## Organisation du repertoire

auto-connexion: Contient la tâche en attente d'un serveur TCP sur le port 1337
segway-ui: Serveur web (interface du segway)
test: simulateur de serveur TCP, en ecoute sur le port 1337
