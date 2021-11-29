# Analisis de Complejidad 🖥️ ✅

## Daniel Rodriguez Figueroa   A01612889

### Add

El algoritmo **(Add)** lleva a cabo dos funciones, una inserta el nodo de acuerdo a su valor y la otra función (**splay**) rota y ordena el árbol (solo si es necesario) para que el nuevo valor ingresado sea la raíz del arbol.
Debido a esto su complejidad es de **O(log n)** para el peor de los casos.

### Remove

El algoritmo **(Remove)** lo utilizamos para remover un nodo del árbol y para ordenar nuevamente el árbol con un (***splay***) para asi poder asignar a su sucesor como raíz, este algoritmo tiene que recorrer **n** pasos.
Debido a esto su complejidad es de **O(log n)** para el peor de los casos.

### Find

El algoritmo **(Find)** recorre **n** pasos recursivamente para completar su busqueda, si encuentra el valor, el algoritmo ejecutará la función ***splay*** para poder asignar el valor encontrado ahora como la raíz del árbol.
Debido a esto su complejidad es de **O(log n)** para el peor de los casos.

### Size

El algoritmo **(Size)** solo devuelve el atributo de tamaño.
Debido a esto su complejidad es de **O(1)** para el peor de los casos.