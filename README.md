# Solarus v2
#### *A small, physics based spaceship game. Loosely based on the space battles from the Star Wars Battlefront videogames. Can pick from a variety of ships to get in, and go to the right to shoot the big bad brain.*

-------------

#### Debug Mode

![](https://i.imgur.com/kDmyhY0.gif)

The physics system implemented allows for hitboxes to be made up of any number of convex polygons. It also uses a quadtree for increased efficiency when numerous physics entities are present in the calculations.

You can see this visualized in the gif above:
- purple lines -> hitbox outline
- red lines -> axis-aligned bounding box
- green lines -> sectors of the quadtree

Developed by:
- Matt Mayer
- Kyle Causton
