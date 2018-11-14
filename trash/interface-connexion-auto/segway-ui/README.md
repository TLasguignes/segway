# Segway User Interface

> Responsive user interface to diplay and pilot the segway

## Déscription des composants

### Store et Vuex

Dans main.js les variables qui vont définir l'état de l'application sont définis dans un store.
L'utilisation du paquet vuex-socketio-plugin permet de gérer le websocket directement dans ce store.
On y a donc des mutations qui permettent de modifier les variable d'état. Ainsi que les actions qui vont permettre de réalisé les envoies.
Les composants décrit ci-dessous sont donc lié avec ce store.

Pour le moment les variables principales sont mis à jour via un message reçu sous le topic "test". Par exemple :  
```
{
    "arret_urgence":false,
    "presence_user":true,
    "position_angulaire":0,
    "vitesse_angulaire": 100,
    "vitesse_lineaire": 50,
    "battery": 90
}
```

Pour plus de détails voici la  [Documentation officiel](https://vuex.vuejs.org/).

### Button
Button permet de créer un bouton ressemblant à ceux d'une mannette de PS4. Il faut par contre indiqué avec la proprité "type" le type de bouton.
Le composant fera appelle  à l'action send du store pour envoyer un message sur le socket indiquant si un clique à eu lieu sur lui.
```
{
    type: 'button',
    data: 'square'
}
```

### Gauge
Implémenté avec GaugeJS, c'est une entrée qui affiche sous forme de jauge une valeur numérique.
Ce composant à 3 paramétres :
- data_store correspond au nom de la variable qui doit être lier à la jauge. Cette variable doit obligatoirement être déclaré dans le store.
- unit correspond à la valeur en unité de la jauge
- label qui correspond au nom de la jauge

### Joystick
Implémenté avec le package NippleJS. Cette élément ne prends aucune propriété en entrée.
Il envoie automatiquement à chaque modification les valeurs x et y du joystick sous la forme suivante :
```
{
    type: 'joystick',
    data: {
        x: 0,
        y: 0
    }
}
```

### Led
Led est une représentation d'un voyant rouge/vert.
Le voyant prends la couleur rouge à l'état faux et vert à l'état vrai.
Il a 3 propriété à renseigné : 
- label
- taille
- value

### Segway
Petite annimation qui représente le Segway bougé en fonction de la valeur de l'angle reçu. (L'image peut être changé).
Il n'y a pas de propriété. Il est cependant necessaire d'avoir dans le store une variable qui s'appelle "angle" qui doit correspondre en degrés à la position angulaire du segway.

## Build Setup

``` bash
# install dependencies
npm install

# serve with hot reload at localhost:8080
npm run dev

# build for production with minification
npm run build

# build for production and view the bundle analyzer report
npm run build --report
```
## 

For a detailed explanation on how things work, check out the [guide](http://vuejs-templates.github.io/webpack/) and [docs for vue-loader](http://vuejs.github.io/vue-loader).
