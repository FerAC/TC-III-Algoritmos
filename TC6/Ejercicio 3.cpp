//Puedo hacer un recorrido con siguiente, hasta que este sea null
//Despues puedo revisar 

copiarGrafo(Grafo original){
    if(!original.vacio()){
        copia.Iniciar();
        Dvv.Iniciar(); //Diccionario de vertices visitados
        int verticesInsertados; 
        for( verticeActual = original.PrimerVertice(); verticesInsertados<original.numVertices(); verticeActual = original.SiguienteVertice(verticeActual)){ //Me muevo por los vertices del grafo
           if(!Dvv.Pert(verticeActual)){ //Si no lo he agregado lo agrego
                copia.AgregarVertice(original.getEtiqueta(verticeActual));
                Dvv.Agregar(verticeActual);
                verticesInsertados++;
           }
            //Veo cuales son los vertices adyacentes al vertice actual
            for(verticeAdyacenteActual = original.PrimerVerticeAdyacente(verticeActual); verticeAdyacenteActual!=NULL; verticeAdyacenteActual= original.siguienteVerticeAdyacente(verticeAdyacenteActual)){
                //Si no lo he agregado lo agrego
                if(!Dvv.Pert(verticeAdyacenteActual)){ //Si no lo he agregado lo agrego
                    copia.AgregarVertice(original.getEtiqueta(verticeAdyacenteActual));
                    Dvv.Agregar(verticeAgyacenteActual);
                    verticesInsertados++;
                }
                //Agrego la arista existente de vertice actual al adyacente (si no existe ya)
                if(!copia.existeArista(verticeActual, verticeAdyacenteActual)){
                    copia.agregarArista(verticeActual, verticeAdyacenteActual, original.Peso(verticeActual, verticeAdyacenteActual));
                }
            }
        }
        Dvv.Destruir(); 

       /*
       int verticesInsertados = 0;
       int verticesTotales = original.numVertices();
       while(verticesInsertados<verticesTotales){
            

       }
       */










    }
}