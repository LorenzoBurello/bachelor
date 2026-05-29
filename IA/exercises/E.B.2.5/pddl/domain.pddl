;Header and description

(define (domain domino_costs)


(:requirements :strips :typing :negative-preconditions :equality)

(:types 
    domino
    value
    cost
)

(:constants 
    n1 n2 n3 n4 n5 n6 - value
)

(:predicates 
    (DominoRight ?d - domino ?r - value)
    (DominoLeft ?d - domino ?l - value)
    (Inserted ?d - domino)
    (LastNumber ?n - value)
    (Clear)
    (TotCost ?c - cost)
    (ActionCost1 ?ci - cost ?cf - cost)
    (ActionCost2 ?ci - cost ?cf - cost)
)

(:action InsertFirst
    :parameters (?d - domino ?r - value ?ci - cost ?cf - cost)
    :precondition (and 
                    (Clear)
                    (DominoRight ?d ?r)
                    (TotCost ?ci)
                    (ActionCost1 ?ci ?cf)
    )
    :effect (and 
                (not (Clear))
                (Inserted ?d)
                (LastNumber ?r)
                (not (TotCost ?ci))
                (TotCost ?cf)
    )
)

(:action InsertFirstRotated
    :parameters (?d - domino ?l - value ?ci - cost ?cf - cost)
    :precondition (and 
                    (Clear)
                    (DominoLeft ?d ?l)
                    (TotCost ?ci)
                    (ActionCost2 ?ci ?cf)
    )
    :effect (and 
                (not (Clear))
                (Inserted ?d)
                (LastNumber ?l)
                (not (TotCost ?ci))
                (TotCost ?cf)
    )
)

(:action Insert
    :parameters (?d - domino ?l - value ?r - value ?last - value ?ci - cost ?cf - cost)
    :precondition (and 
                    (not(Inserted ?d))
                    (DominoRight ?d ?r)
                    (DominoLeft ?d ?l)
                    (LastNumber ?last)
                    (= ?l ?last)
                    (TotCost ?ci)
                    (ActionCost1 ?ci ?cf)
    )
    :effect (and 
                (Inserted ?d)
                (not(LastNumber ?last))
                (LastNumber ?r)
                (not (TotCost ?ci))
                (TotCost ?cf)
    )
)

(:action InsertRotated
    :parameters (?d - domino ?l - value ?r - value ?last - value ?ci - cost ?cf - cost)
    :precondition (and 
                    (not(Inserted ?d))
                    (DominoRight ?d ?r)
                    (DominoLeft ?d ?l)
                    (LastNumber ?last)
                    (= ?r ?last)
                    (TotCost ?ci)
                    (ActionCost2 ?ci ?cf)
    )
    :effect (and 
                (Inserted ?d)
                (not(LastNumber ?last))
                (LastNumber ?l)
                (not (TotCost ?ci))
                (TotCost ?cf)
    )
)


)