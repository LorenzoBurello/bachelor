;Header and description

(define (domain Charlie)


(:requirements :strips :typing :negative-preconditions :equality)

(:types 

    x
    y
)

(:predicates 
    (HasBanana)
    (HasLadder)
    (Ladder ?x - x ?y - y)
    (Charlie ?x - x ?y - y)
    (Block ?x - x ?y - y)
    (Banana ?x - x?y - y)
    (Available ?x - x ?y - y)
    (AdiacentX ?x1 - x ?x2 - x)
    (AdiacentY ?y1 - y ?y2 - y)
)

(:action TakeLadder
    :parameters (?x - x ?y - y)
    :precondition (and 
                    (Charlie ?x ?y)
                    (Ladder ?x ?y)              
    )
    :effect (and 
                (not (Ladder ?x ?y))
                (HasLadder)
    )
)

(:action PlaceLadder
    :parameters (?x - x ?y - y)
    :precondition (and 
                    (Charlie ?x ?y)
                    (HasLadder)
    )
    :effect (and 
                (not (HasLadder))
                (Ladder ?x ?y)
    )
)

(:action MoveStraight
    :parameters (?x_src - x ?x_dst - x ?y - y)
    :precondition (and 
                    (Charlie ?x_src ?y)
                    (AdiacentX ?x_src ?x_dst)
                    (Available ?x_dst ?y)
    )
    :effect (and 
                (not(Charlie ?x_src ?y))
                (Charlie ?x_dst ?y)
    )
)

(:action MoveOneBlockHeight
    :parameters (?x1 - x ?y1 - y ?x2 - x ?y2 - y)
    :precondition (and 
                    (Charlie ?x1 ?y1)
                    (AdiacentX ?x1 ?x2)
                    (AdiacentY ?y1 ?y2)
                    (Available ?x2 ?y2)
    )
    :effect (and 
                (not (Charlie ?x1 ?y1))
                (Charlie ?x2 ?y2)
    )
)

(:action MoveTwoBlockHeight
    :parameters (?x1 - x ?y1 - y ?x2 - x ?y2 - y ?y3 - y)
    :precondition (and 
                    (AdiacentX ?x1 ?x2)
                    (AdiacentY ?y1 ?y3)
                    (AdiacentY ?y1 ?y2)
                    (not (= ?y1 ?y2))
                    (Charlie ?x1 ?y1)
                    (Available ?x2 ?y2)
    )
    :effect (and 
                (not (Charlie ?x1 ?y1))
                (Charlie ?x2 ?y2)
    )
)

(:action Dig
    :parameters (?x - x ?y1 - y ?y2 - y)
    :precondition (and 
                    (Charlie ?x ?y1)
                    (Block ?x ?y2)
                    (AdiacentY ?y1 ?y2)
    )
    :effect (and 
                (not (Available ?x ?y1))
                (not (Charlie ?x ?y1))
                (not (Block ?x ?y2))
                (Available ?x ?y2)
                (Charlie ?x ?y2)
    )
)

(:action TakeBanana
    :parameters (?x - x ?y1 - y ?y2 - y)
    :precondition (and 
                    (Charlie ?x ?y1)
                    (Banana ?x ?y2)
                    (AdiacentY ?y1 ?y2)
    )
    :effect (and 
                (not (Banana ?x ?y2))
                (HasBanana)
    )
)

(:action MoveBlock
    :parameters (?x_c - x ?y_cb - y ?x_b - x ?y_b_av - y ?x_dst - x ?y_dst - y ?y_dst_av - y)
    :precondition (and 
                    (AdiacentX ?x_c ?x_b)
                    (AdiacentX ?x_b ?x_dst)
                    (not (= ?x_c ?x_dst))
                    (AdiacentY ?y_cb ?y_b_av)
                    (AdiacentY ?y_dst_av ?y_dst)
                    (not (Block ?x_dst ?y_dst_av))
                    (Charlie ?x_c ?y_cb)
                    (Block ?x_b ?y_cb)
                    (Available ?x_b ?y_b_av)
                    (not (Block ?x_dst ?y_cb))
                    (Available ?x_dst ?y_dst)
                    (not (Ladder ?x_dst ?y_dst))
    )
    :effect (and 
                (not (Charlie ?x_c ?y_cb))
                (not (Block ?x_b ?y_cb))
                (not (Available ?x_b ?y_b_av))
                (not (Available ?x_dst ?y_dst))
                (Charlie ?x_b ?y_cb)
                (Available ?x_b ?y_cb)
                (Block ?x_dst ?y_dst)
                (Available ?x_dst ?y_dst_av)
    )
)

(:action MoveBlockOnLadder
    :parameters (?x_c - x ?y_cbl - y ?x_b - x ?x_l - x ?y_dst - y ?x_dst - x ?y_dst_av - y)
    :precondition (and 
                    (AdiacentY ?y_dst ?y_cbl)
                    (Available ?x_b ?y_dst)
                    (Charlie ?x_c ?y_cbl)
                    (Block ?x_b ?y_cbl)
                    (Ladder ?x_l ?y_cbl)
                    (Available ?x_dst ?y_dst)
                    (AdiacentY ?y_dst_av ?y_dst)
                    (not (Block ?x_dst ?y_dst_av))
    )
    :effect (and 
                (not (Block ?x_b ?y_cbl))
                (Block ?x_dst ?y_dst)
                (not (Charlie ?x_c ?y_cbl))
                (Charlie ?x_l ?y_cbl)
                (not (Available ?x_b ?y_dst))
                (Available ?x_b ?y_cbl)
                (not (Available ?x_dst ?y_dst))
                (Available ?x_dst ?y_dst_av)
    )
)


)