(define (domain domino)

(:requirements :strips :typing :negative-preconditions :equality)

(:types 
    domino
    value
)

(:constants 
    n1 n2 n3 n4 n5 n6 - value
)

(:predicates 
    (DominoNumber ?d - domino ?n - value)
    (Inserted ?d - domino)
    (LastNumber ?n - value)
    (Clear)
    (Finished)

)

(:action InsertFirst
    :parameters (?d - domino ?r - value)
    :precondition (and 
                    (Clear)
                    (not (Inserted ?d))
                    (DominoNumber ?d ?r)
    )
    :effect (and 
                (not (Clear))
                (LastNumber ?r)
                (Inserted ?d)
    )
)
(:action Insert
    :parameters (?d - domino ?l - value ?r - value ?last - value)
    :precondition (and 
                    (not (Clear))
                    (not (Inserted ?d))
                    (DominoNumber ?d ?r)
                    (DominoNumber ?d ?l)
                    (LastNumber ?last)
                    (= ?l ?last)
                    (not(= ?l ?r))
    )
    :effect (and 
                (Inserted ?d)
                (not (LastNumber ?last))
                (LastNumber ?r)
    )
)
)