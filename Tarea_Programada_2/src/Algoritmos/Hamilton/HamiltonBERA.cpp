#include "AuxiliaresHamiltonBERA.hpp"

// #include <iostream> // DEBUG
#include <queue>  // Cola de prioridad
#include <set>  // Diccionarios

static size_t MinimoCostoPosible(const Grafo& grafo
    , const Estado& estadoActual) {
    // Llevemos cuenta del peso estimado al momento
    size_t costoEstimado = 0;

    // Visitemos cada vertice
    for (Vertice v = grafo.PrimerVertice(); v != Vertice(); v = grafo.SiguienteVertice(v)) {

        // Solo debemos considerar dos aristas por vertice
        char aristasConsideradas = 0;
        std::priority_queue<Arista, std::vector<Arista>, std::greater<Arista>> aristasPorConsiderar;

        // Visitemos cada uno de sus vecinos adyacentes
        for (Vertice w = grafo.PrimerVerticeAdyacente(v); w != Vertice() && aristasConsideradas < 2
        ; w = grafo.SiguienteVerticeAdyacente(v, w)) {

            // Consideremos la arista que hay entre ambos
            Arista aristaActual(v, w, grafo.Peso(v, w));

            // Si definitivamente ya la consideramos, entonces añadámosla al costo estimado
            if (estadoActual.aristasAceptadas.contains(aristaActual)) {

                /* DEBUG */
               // std::cout << "\tSumando [" << grafo.Etiqueta(v) << ", " << grafo.Etiqueta(w) << "] al estimado" 
               // << std::endl; /**/

                costoEstimado += aristaActual.pesoAsociado;
                aristasConsideradas += 1;
            
            } 
             // Sino, si no la omitimos, añadamosla a las aristas por considerar
            else if (!estadoActual.aristasDescartadas.contains(aristaActual)) {
                aristasPorConsiderar.push(aristaActual);
            }
        }

        // Si todavía nos falta 2 aristas por considerar, entonces revisemoslas
        if (aristasConsideradas < 2) {
            // Si podemos revisar 2 aristas, obtengamoslas priorizando el menor costo
            if (aristasPorConsiderar.empty()) {
                continue;
            }

            /* DEBUG */
            //std::cout << "\tSumando [" << grafo.Etiqueta(aristasPorConsiderar.top().first) << ", " 
           // << grafo.Etiqueta(aristasPorConsiderar.top().second) << "] al estimado" 
            //<< std::endl; /**/

            costoEstimado += aristasPorConsiderar.top().pesoAsociado;
            aristasPorConsiderar.pop();
            aristasConsideradas += 1;


            if (aristasPorConsiderar.empty() || aristasConsideradas == 2) {
                continue;
            }

            /* DEBUG */
            //std::cout << "\tSumando [" << grafo.Etiqueta(aristasPorConsiderar.top().first) << ", " 
            //<< grafo.Etiqueta(aristasPorConsiderar.top().second) << "] al estimado" 
            //<< std::endl; /**/

            costoEstimado += aristasPorConsiderar.top().pesoAsociado;
            aristasPorConsiderar.pop();
        }
    }

    // Ya el costo está estimado
    return costoEstimado;
}

static size_t CostoRecorrido(const Grafo& grafo
    , const std::vector<Vertice>& recorrido) {
    size_t costoTotal = 0;
    
    // Recorreremos todas los vértices en el circuito
    // y consideraremos sus aristas, garantizadas por
    // la factibilidad
    for (size_t it = 0; it < recorrido.size(); ++it) {
        if (it == 0) {
            // DEBUG
           // std::cout << "Costo recorrido += [" << grafo.Etiqueta(recorrido.back()) 
            //<< ", " << grafo.Etiqueta(recorrido[0]) << "]" << std::endl;
            
            costoTotal += 
                grafo.Peso(recorrido.back(), recorrido[0]);
        } else {
            // DEBUG
            //std::cout << "Costo recorrido += [" << grafo.Etiqueta(recorrido[it-1]) 
            //<< ", " << grafo.Etiqueta(recorrido[it]) << "]" << std::endl;

            costoTotal += 
                grafo.Peso(recorrido[it-1], recorrido[it]);
        }
    }

    // Para ser comparable con los costos mínimos, debemos artificalmente
    // inflar este costo x2, para representar la doble-vía entre vértices
    // que sí considera la función de costo mínimo
    return 2*costoTotal;
}

static bool EsPosiblementeFactible(const Grafo& grafo
    , const Estado& estadoActual
    , const Soluciones& solucionesActuales) {

    // Llevemos cuenta de cuántos vértices se han agregado a la solución actual
    const size_t verticesAlMomento = solucionesActuales.solucionActual.size();

    // Si no hemos añadido al menos dos vértices a la solución actual, entonces consideramos
    // que existe potencial para factibilidad
    if (verticesAlMomento < 2) {
        return true;
    }

    // Revisaremos si el último vértice conecta con su anterior
    if (!grafo.ExisteArista(solucionesActuales.solucionActual[verticesAlMomento - 2]
        , solucionesActuales.solucionActual.back()))
        return false;

    // También llevemos cuenta del último vértice del recorrido
    const Vertice& verticeFinal = solucionesActuales.solucionActual.back();
    
    // Si ya recorrimos todos los vértices, hay que revisar si el último
    // vertice conecta con el primero
    if (verticesAlMomento == grafo.NumVertices())
    {
        const Vertice& verticeInicial = solucionesActuales.solucionActual.front();
        char puedeCerrarCiclo = 0;

        for (Vertice adyacente = grafo.PrimerVerticeAdyacente(verticeFinal);
        adyacente != Vertice() && puedeCerrarCiclo == 0; 
        adyacente = grafo.SiguienteVerticeAdyacente(verticeFinal, adyacente)) {
            if (adyacente == verticeInicial) {
                puedeCerrarCiclo = 1;
            }
        }
        
        // Solo esta solución es factible solo si logramos cerrar el ciclo
        return puedeCerrarCiclo == 1;
    }
    
    // Sino, debemos revisar conexiones del último vértice en el recorrido
    // Si es adyacente con algún vértice no visitado al momento, entonces esta
    // solución tiene potencial de ser factible
    char tieneAdyacenteValido = 0;
    for (Vertice verticeAdyacente = grafo.PrimerVerticeAdyacente(verticeFinal);
    verticeAdyacente != Vertice() && tieneAdyacenteValido == 0;
    verticeAdyacente = grafo.SiguienteVerticeAdyacente(verticeFinal, verticeAdyacente)) {
        if (!estadoActual.verticesRecorridos.contains(verticeAdyacente)) {
            tieneAdyacenteValido = 1;
        }
    }

    if (tieneAdyacenteValido == 1)
        return true;

    // Sino, entonces esta solución de fijo no tiene puede terminar el ciclo hamiltoniano,
    // por lo que no tiene el potencial de ser factible
    return false;
}

static const Vertice ConsiderarVerticeHamiltonBERA(const Grafo& grafo
    , const Vertice& verticePorConsiderar
    , Estado& estadoActual
    , Soluciones& solucionesActual) {
    const Vertice& verticeFinal = solucionesActual.solucionActual.back();
    Arista aristaPorConsiderar(verticeFinal, verticePorConsiderar, grafo.Peso(verticeFinal, verticePorConsiderar));

    // Hay que actualizar las E.D acordemente
    if (!estadoActual.verticesRecorridos.contains(verticePorConsiderar)) {
        solucionesActual.solucionActual.push_back(verticePorConsiderar);
        estadoActual.verticesRecorridos.insert(verticePorConsiderar);
    }
    estadoActual.aristasAceptadas.insert(aristaPorConsiderar);
    estadoActual.aristasDescartadas.erase(aristaPorConsiderar);

    // DEBUG
    // std::cout << "Solucion actual tras considerar:" << std::endl;
    // for (size_t i = 0; i < solucionesActual.solucionActual.size(); ++i) {
    //     std::cout << solucionesActual.solucionActual[i].getEtiqueta() << " ";
    // }
    // std::cout << std::endl;

    // Consideraremos al primer vértice ocioso adyacente del vértice añadido
    // La condición de factibilidad nos garantiza que debe existir uno
    Vertice verticeAdyacenteLibre = grafo.PrimerVerticeAdyacente(verticePorConsiderar);
    while (estadoActual.verticesRecorridos.contains(verticeAdyacenteLibre)
        || estadoActual.aristasDescartadas.contains(
        Arista(verticePorConsiderar
            , verticeAdyacenteLibre
            , grafo.Peso(verticePorConsiderar
            , verticeAdyacenteLibre)
            )
        )) {
        verticeAdyacenteLibre = grafo.SiguienteVerticeAdyacente(verticePorConsiderar
            , verticeAdyacenteLibre);
    }

    // DEBUG
    if (estadoActual.verticesRecorridos.contains(verticeAdyacenteLibre)
        || estadoActual.aristasDescartadas.contains(
        Arista(verticePorConsiderar
            , verticeAdyacenteLibre
            , grafo.Peso(verticePorConsiderar
            , verticeAdyacenteLibre)
            )
        ))
        return Vertice();

    return verticeAdyacenteLibre;
}

static const Vertice DescartarVerticeHamiltonBERA(const Grafo& grafo
    , const Vertice& verticePorDescartar
    , Estado& estadoActual
    , Soluciones& solucionesActual) {
    // Hay que actualizar las E.D acordemente
    if (estadoActual.verticesRecorridos.contains(verticePorDescartar)) {
        solucionesActual.solucionActual.pop_back();
        estadoActual.verticesRecorridos.erase(verticePorDescartar);
    }

    const Vertice& verticeFinal = solucionesActual.solucionActual.back();
    Arista aristaPorDescartar(verticeFinal, verticePorDescartar, grafo.Peso(verticeFinal, verticePorDescartar));
    
    estadoActual.aristasAceptadas.erase(aristaPorDescartar);
    estadoActual.aristasDescartadas.insert(aristaPorDescartar);

    // DEBUG
    //std::cout << "Solucion actual tras descartar:" << std::endl;
    
    //std::cout << std::endl;

    // Si se nos acabaron los vértices, devolveremos un vértice nulo
    if (solucionesActual.solucionActual.size() == 0) {
        return Vertice();
    }

    // Consideraremos al primer vértice ocioso adyacente del vértice previo
    // La condición de factibilidad nos garantiza que debe existir uno
    Vertice verticeAdyacenteLibre = grafo.PrimerVerticeAdyacente(solucionesActual.solucionActual.back());
    while (estadoActual.verticesRecorridos.contains(verticeAdyacenteLibre)
        || estadoActual.aristasDescartadas.contains(
        Arista(solucionesActual.solucionActual.back()
            , verticeAdyacenteLibre
            , grafo.Peso(solucionesActual.solucionActual.back()
            , verticeAdyacenteLibre)
            )
        )) {
        verticeAdyacenteLibre = grafo.SiguienteVerticeAdyacente(verticePorDescartar
            , verticeAdyacenteLibre);
    }

    // DEBUG
    if (estadoActual.verticesRecorridos.contains(verticeAdyacenteLibre)
        || estadoActual.aristasDescartadas.contains(
        Arista(solucionesActual.solucionActual.back()
            , verticeAdyacenteLibre
            , grafo.Peso(solucionesActual.solucionActual.back()
            , verticeAdyacenteLibre)
            )
        ))
        return Vertice();

    return verticeAdyacenteLibre;
}

static void BacktrackConsideracionHamiltonBERA(const Grafo& grafo
, const Vertice& verticeConsiderado
, Estado& estadoActual
, Soluciones& solucionesActual) {
    // Quitemos al vértice de los vértices recorridos
    estadoActual.verticesRecorridos.erase(verticeConsiderado);

    // Quitemos al vértice de la solución actual
    if (!solucionesActual.solucionActual.empty()) {
        if (verticeConsiderado == solucionesActual.solucionActual.back()) {
            solucionesActual.solucionActual.pop_back();
        }
    }

    // Quitemos la arista correspondiente de las aceptadas
    if (!solucionesActual.solucionActual.empty()) {

        estadoActual.aristasAceptadas.erase(
            Arista(solucionesActual.solucionActual.back()
            , verticeConsiderado
            , grafo.Peso(solucionesActual.solucionActual.back(), verticeConsiderado)));
    }

    // El estado previo a sido restaurado
    return;
}

static void BacktrackDescarteHamiltonBERA(const Grafo& grafo
, const Vertice& verticeConsiderado
, Estado& estadoActual
, Soluciones& solucionesActual) {
    // Quitemos al vértice de los vértices recorridos
    estadoActual.verticesRecorridos.erase(verticeConsiderado);

    // Quitemos la arista correspondiente de las prohibidas
    if (!solucionesActual.solucionActual.empty()) {

        estadoActual.aristasDescartadas.erase(
            Arista(solucionesActual.solucionActual.back()
            , verticeConsiderado
            , grafo.Peso(solucionesActual.solucionActual.back(), verticeConsiderado)));
    }

    // El estado previo a sido restaurado
    return;
}

static bool HamiltonBERARecursivo(const Grafo& grafo
    , const Vertice& verticePorConsiderar
    , Estado& estadoActual
    , Soluciones& solucionesActual) {
    // DEBUG
    //std::cout << "=============================" << std::endl;

    // Si ya completamos el recorrido, quizás tengamos una solución factible
    if (solucionesActual.solucionActual.size() == grafo.NumVertices()) {

        // Encontramos una solución factible
        if (EsPosiblementeFactible(grafo, estadoActual, solucionesActual)) {
            // Si tenemos una solución factible, debemos actualizar su costo
            solucionesActual.costoSolucionActual 
                = CostoRecorrido(grafo, solucionesActual.solucionActual);

            // DEBUG
           /// std::cout << "Solución factible encontrada, con costo " << solucionesActual.costoSolucionActual << std::endl;

            // Si la solución factible es superior a la mejor, hay que sustituir a la mejor
            if (solucionesActual.costoSolucionActual < solucionesActual.costoMejorSolucion) {
                solucionesActual.mejorSolucion = solucionesActual.solucionActual;
                solucionesActual.costoMejorSolucion = solucionesActual.costoSolucionActual;
            }
        }
        // Si no hay solución factible al final del recorrido, hay que propagar el error
        else {
            return false;
        }
    }

    // Sino, si el vértice nuevo es nulo, no hay nada que se pueda hacer
    if (verticePorConsiderar == Vertice()) {
        // DEBUG
        //std::cout << "Vertice nulo " << std::endl;
        return false;
    }

    // DEBUG
    // std::cout << "Vertice considerado: " << verticePorConsiderar.getEtiqueta() << std::endl;

    // DEBUG
    //std::cout << "Solucion actual: " << std::endl;
    
    //std::cout << std::endl;

    bool potencialFactibilidadCon = !estadoActual.aristasDescartadas.contains(
        Arista(solucionesActual.solucionActual.back(), verticePorConsiderar
        , grafo.Peso(solucionesActual.solucionActual.back(), verticePorConsiderar)));

    bool potencialFactibilidadSin = !estadoActual.aristasAceptadas.contains(
        Arista(solucionesActual.solucionActual.back(), verticePorConsiderar
        , grafo.Peso(solucionesActual.solucionActual.back(), verticePorConsiderar)));

    //     DEBUG
    //    std::cout << "Aristas prohibidas:" << std::endl;
    //    for (auto it = estadoActual.aristasDescartadas.begin(); it != estadoActual.aristasDescartadas.end(); ++it)
    //    {
    //        std::cout << "[" << grafo.Etiqueta(it->first) << "," << grafo.Etiqueta(it->second) << "] ";
    //    }
    //    std::cout << std::endl;

    //     DEBUG
    //     std::cout << "Aristas obligatorias:" << std::endl;
    //    for (auto it = estadoActual.aristasAceptadas.begin(); it != estadoActual.aristasAceptadas.end(); ++it)
    //    // {
    //        std::cout << "[" << grafo.Etiqueta(it->first) << "," << grafo.Etiqueta(it->second) << "] ";
    //    }
    //     std::cout << std::endl;

    // DEBUG
    // std::cout << "Vertices visitados:" << std::endl;
    // for (auto it = estadoActual.verticesRecorridos.begin(); it != estadoActual.verticesRecorridos.end(); ++it)
    // {
    //     std::cout << grafo.Etiqueta(*it) << " ";
    // }
    // std::cout << std::endl;

    // DEBUG
    // std::cout 
    // << "Con implica violar una arista descartada? " << ((!potencialFactibilidadCon)? "si" : "no")
    //     << std::endl
    // << "Sin implica violar una arista descartada? " << ((!potencialFactibilidadSin)? "si" : "no")
    //     << std::endl;

    // Revisaremos la factibilidad sin considerar al vértice nuevo
    Vertice previoAConsiderar = DescartarVerticeHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);
    if (potencialFactibilidadSin) {
        // DBEUG
     //   std::cout << "Considerando factibilidad sin..." << std::endl;
    
        potencialFactibilidadSin = EsPosiblementeFactible(grafo, estadoActual, solucionesActual);
    }

    // Y el costo respectivo
    size_t costoSin = ((potencialFactibilidadSin)? 
        MinimoCostoPosible(grafo, estadoActual) : std::numeric_limits<size_t>::max());

    // Como también revisaremos la factibilidad considerando al vértice nuevo
    Vertice trasConsiderar = ConsiderarVerticeHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);
    if (potencialFactibilidadCon) {
        // DBEUG
        // std::cout << "Considerando factibilidad con..." << std::endl;

        potencialFactibilidadCon = EsPosiblementeFactible(grafo, estadoActual, solucionesActual);
    }

    // Y el costo respectivo
    size_t costoCon = ((potencialFactibilidadCon)? 
        MinimoCostoPosible(grafo, estadoActual) : std::numeric_limits<size_t>::max());

    // DEBUG
    // std::cout 
    // << "Costo mejor solucion actual " << solucionesActual.costoMejorSolucion
    //     << std::endl
    // << "Costo con: " << costoCon 
    //     <<  ", potencialmente factible: " << ((potencialFactibilidadCon)? "si" : "no")
    //     << std::endl
    //     << "\tOptimiza solucion: " << ((costoCon < solucionesActual.costoMejorSolucion)? "si" : "no")
    //     << std::endl
    // << "Costo sin: " << costoSin 
    //     << ", potencialmente factible: " << ((potencialFactibilidadSin)? "si" : "no")
    //     << std::endl
    //     << "\tOptimiza solucion: " << ((costoSin < solucionesActual.costoMejorSolucion)? "si" : "no")
    //     << std::endl;

    // Visitaremos a las sub-ramas de posibilidad según el orden de costo, solo si son factibles
    char factibilidadCon = 0;
    char factibilidadSin = 0;
    char visitadoConPrimero = 0;
    if (costoCon < costoSin && potencialFactibilidadCon) {
        // DEBUG
        // std::cout << "Visitando con primero" << std::endl;

        visitadoConPrimero = 1;
        // Intentaremos realizar el recorrido recursivo
        if (HamiltonBERARecursivo(grafo, trasConsiderar, estadoActual, solucionesActual))
            factibilidadCon = 1;
    }
    else if (potencialFactibilidadSin) {
        // DEBUG
        // std::cout << "Visitando sin primero" << std::endl;

        // Quitaremos al vértice añadido a la solución actual
        DescartarVerticeHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);

        // Ahora intentaremos realizar el recorrido recursivo
        if (HamiltonBERARecursivo(grafo, previoAConsiderar, estadoActual, solucionesActual))
            factibilidadSin = 1;
    }

    // Si existe solución del sub-árbol de posibilidades, entonces compararemos su costo
    // con la siguiente rama

    // Si resulta que existe potencial de optimizar revisando la otra rama, la investigaremos
    if (visitadoConPrimero == 1
        && potencialFactibilidadSin
        && costoSin < solucionesActual.costoMejorSolucion) {
        // DEBUG
        // std::cout << "Visitando sin segundo" << std::endl;

        previoAConsiderar = DescartarVerticeHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);
        factibilidadSin = HamiltonBERARecursivo(grafo, previoAConsiderar, estadoActual, solucionesActual);

        // Y ahora retrocederemos el estado al previo
        BacktrackDescarteHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);
    } 
    
    else if (visitadoConPrimero == 0
        && potencialFactibilidadCon
        && costoCon < solucionesActual.costoMejorSolucion) {
        // DEBUG
        // std::cout << "Visitando con segundo" << std::endl;

        trasConsiderar = ConsiderarVerticeHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);
        factibilidadCon = HamiltonBERARecursivo(grafo, trasConsiderar, estadoActual, solucionesActual);

        // Y ahora retrocederemos el estado al previo
        BacktrackConsideracionHamiltonBERA(grafo, verticePorConsiderar, estadoActual, solucionesActual);
    }

    // std::cout << "Recorridos terminados" << std::endl;

    // Ya terminamos de explorar el sub-árbol de soluciones de esta iteración.
    // Podemos propagar la factibilidad de esta rama hacia arriba
    return factibilidadCon == 1 || factibilidadSin == 1;
}

namespace Algoritmos {

    std::vector<Vertice> HamiltonBERA(const Grafo& grafo) {

        // Llevemos cuenta de la cantidad de vertices en el grafo
        const size_t cantidadVertices = grafo.NumVertices();

        // Si no hay mas de dos vértices, no necesitamos continuar
        if (cantidadVertices <= 1) {
            return std::vector<Vertice>();
        }

        // Para el recorrido con BERA necesitaremos de varias E.D auxiliares:
            // Una referencia al primer vértice del grafo
            const Vertice origenRecorrido = grafo.PrimerVertice();
            // Un registro del estado actual del recorrido
            Estado estado;
            // Y otro registro donde almacenar las soluciones
            Soluciones soluciones;

        // Ahora podemos comenzar el recorrido recursivo
        estado.verticesRecorridos.insert(origenRecorrido);
        soluciones.solucionActual.push_back(origenRecorrido);
        HamiltonBERARecursivo(grafo, grafo.PrimerVerticeAdyacente(origenRecorrido), estado, soluciones);

        // Tras terminar el recorrido, podemos devolver el vector con la mejor solución
        return soluciones.mejorSolucion;
    }
}
