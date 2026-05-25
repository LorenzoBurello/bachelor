;Header and description

(define (domain Charlie)


(:requirements :strips :typing :negative-preconditions :equality)

(:types 

    Coordinate
    Item
    Block - Item
    Charlie - Item
    Ladder - Item ;Header and description

(define (domain Charlie)


(:requirements :strips :typing :negative-preconditions :equality)

(:types 
)




(:predicates 
    (HasBanana)
    (HasLadder)
    (Ladder ?x  ?y )
    (Charlie ?x  ?y )
    (Block ?x  ?y )
    (Banana ?x ?y )
    (Available ?x  ?y )
    (ReachableOne ?c1 ?c2)
    (ReachableTwo ?c1 ?c2)
)

(:action TakeLadder
    :parameters (?x  ?y )
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
    :parameters (?x  ?y )
    :precondition (and 
                    (Charlie ?x ?y)
                    (HasLadder)
    )
    :effect (and 
                (not (HasLadder))
                (Ladder ?x ?y)
    )
)


(:action TakeBanana
    :parameters (?x  ?y1  ?y2 )
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

(:action MoveNoLadder
    :parameters (?x_src ?y_src ?x_dst ?y_dst)
    :precondition (and 
                    (Charlie ?x_src  ?y_src )
                    (ReachableOne ?x_src ?x_dst)
                    (not (= ?x_src ?x_dst))
                    (ReachableOne ?y_src ?y_dst)
                    (Available ?x_dst  ?y_dst)
    )
    :effect (and 
                (not (Charlie ?x_src  ?y_src ))
                (Charlie ?x_dst  ?y_dst )
    )
)

(:action MoveTwoBlockHeight
    :parameters (?x_src  ?y_src  ?x_dst  ?y_dst)
    :precondition (and 
                    (Charlie ?x_src ?y_src)
                    (Ladder ?x_src  ?y_src)
                    (ReachableTwo ?y_src ?y_dst)
                    (not (= ?y_src ?y_dst))
                    (ReachableOne ?x_src ?x_dst)
                    (Available ?x_dst  ?y_dst)
    )
    :effect (and 
                (not (Charlie ?x_src ?y_src))
                (Charlie ?x_dst ?y_dst)
    )
)

(:action Dig
    :parameters (?x  ?y_src  ?y_dst )
    :precondition (and 
                    (Charlie ?x ?y_src)
                    (Block ?x ?y_dst)
                    (ReachableOne ?y_src ?y_dst)
    )
    :effect (and 
                (not (Block ?x ?y_dst))
                (not (Available ?x ?y_src))
                (Available ?x ?y_dst)
                (not (Charlie ?x ?y_src))
                (Charlie ?x ?y_dst)
    )
)

(:action MoveBlock
    :parameters (?x_c  ?y_cb  ?x_b  ?y_b_av  ?x_dst  ?y_dst  ?y_dst_av )
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
    :parameters (?x_c  ?y_cbl  ?x_b  ?x_l  ?y_dst  ?x_dst  ?y_dst_av )
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
    Void - Item
)

(:constants
    c - Charlie
    l - Ladder
    b - Banana
    v - Void
)

(:predicates 
    (HasBanana)
    (HasLadder)
    (On ?b1 - Item ?b2 - Block)
    (Clear ?b - Block)
    (Order ?b1 - Block ?b2 - Block)
    (Ladder ?x  ?y )
    (Charlie ?x  ?y )
    (Block ?x  ?y )
    (Banana ?x ?y )
    (Available ?x  ?y )
    (AdiacentX ?x1  ?x2 )
    (AdiacentY ?y1  ?y2 )
)

(:action TakeLadder
    :parameters (?b - Block)
    :precondition (and 
                    (On l ?b)
                    (On c ?b)              
    )
    :effect (and 
                (not (On l ?b))
                (HasLadder)
    )
)

(:action PlaceLadder
    :parameters (?b - Block)
    :precondition (and 
                    (On c ?b)
                    (HasLadder)
    )
    :effect (and 
                (not (HasLadder))
                (On l ?b)
    )
)

(:action MoveRight
    :parameters (?b1 - Block ?b2 - Block)
    :precondition (and 
                    (On c ?b1)
                    (Clear ?b2)
    )
    :effect (and 
                (not(Charlie ?x_src ?y))
                (Charlie ?x_dst ?y)
    )
)

(:action MoveOneBlockHeight
    :parameters (?x1  ?y1  ?x2  ?y2 )
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
    :parameters (?x1  ?y1  ?x2  ?y2  ?y3 )
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
    :parameters (?x  ?y1  ?y2 )
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
    :parameters (?x  ?y1  ?y2 )
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
    :parameters (?x_c  ?y_cb  ?x_b  ?y_b_av  ?x_dst  ?y_dst  ?y_dst_av )
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
    :parameters (?x_c  ?y_cbl  ?x_b  ?x_l  ?y_dst  ?x_dst  ?y_dst_av )
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