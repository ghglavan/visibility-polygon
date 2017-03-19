This is a project that I've made with <a href ="https://github.com/NeacsuRadu">Neacsu Radu</a>

<b>Input</b>: A polygon P, and A a point inside P.<br>
<b>Output</b>: A graphical reprezentation oh the area inside P that is fisible from A.

The program uses Qt for GUI and I/O operations.

<img src = "gc.png"/>

As shown in the image above, the polygon is created from consecutive points given by the user. After that, the aplication decides if the polygon does not auto-intersect. If not, the points are set in clockwise order and the application gives the triangulation (the red lines). Triangulation is made using the <a href ="https://en.wikipedia.org/wiki/Polygon_triangulation">Ear Clipping Method</a>. Then, the visibility is computed based on the triangulation.
