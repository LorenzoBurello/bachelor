;Header and description

(define (domain Hanoi_towers)

(:requirements :strips :typing :negative-preconditions :equality)

(:types 
    diskortable
    disk - diskortable
    axis
)

(:constants 
    a1 a2 a3 - axis
    table - diskortable
)

(:predicates 
    (On ?a - axis ?d - disk ?dor - diskortable)
    (Top ?a - axis ?dor - diskortable)
    (less ?dor1 - diskortable ?dor2 - diskortable)
)


(:action MoveDisk
    :parameters (?d - disk ?s - diskortable ?t - diskortable ?as - axis ?at - axis)
    :precondition (and 
                    (On ?as ?d ?s)
                    (less ?d ?t)
                    (Top ?as ?d)
                    (Top ?at ?t)
    )
    :effect (and 
                (not (On ?as ?d ?s))
                (not (Top ?as ?d))
                (Top ?as ?s)
                (not (Top ?at ?t))
                (Top ?at ?d)
                (On ?at ?d ?t)
    )
)

)