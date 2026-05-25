;Header and description

(define (domain buckets)


(:requirements :strips :typing :negative-preconditions :equality)

(:types 
    bucket
    quantity
)

(:predicates 
    (Capacity ?b - bucket ?c - quantity)
    (Contains ?b - bucket ?q - quantity)
    (Sum ?a - quantity ?b - quantity ?c - quantity)
    (Le ?a - quantity ?b - quantity)
)


(:action PourAll
    :parameters (?b1 - bucket ?b2 - bucket ?q1i - quantity ?q2i - quantity ?c2 - quantity ?rem - quantity ?q2f - quantity ?z - quantity)
    :precondition (and 
                    (Contains ?b1 ?q1i)
                    (Contains ?b2 ?q2i)
                    (Capacity ?b2 ?c2)
                    (Sum ?q2i ?rem ?c2)
                    (Le ?q1i ?rem)
                    (Sum ?q2i ?q1i ?q2f)
                    (Sum ?z ?z ?z)
    )
    :effect (and 
                (not (Contains ?b1 ?q1i))
                (Contains ?b1 ?z)
                (not (Contains ?b2 ?q2i))
                (Contains ?b2 ?q2f)
    )
)
(:action PourSome
    :parameters (?b1 - bucket ?b2 - bucket ?q1i - quantity ?q2i - quantity ?c2 - quantity ?rem - quantity ?q1f - quantity)
    :precondition (and 
                    (Contains ?b1 ?q1i)
                    (Contains ?b2 ?q2i)
                    (Capacity ?b2 ?c2)
                    (Sum ?q2i ?rem ?c2)
                    (not (Le ?q1i ?rem))
                    (Sum ?rem ?q1f ?q1i)
    )
    :effect (and 
                (not (Contains ?b1 ?q1i))
                (Contains ?b1 ?q1f)
                (not (Contains ?b2 ?q2i))
                (Contains ?b2 ?c2)
    )
)
)