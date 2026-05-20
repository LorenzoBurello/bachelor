(define (problem six_dominos) (:domain domino)
(:objects 
    D1 D2 D3 D4 D5 D6 - domino
)

(:init
    (DominoNumber D1 n2)
    (DominoNumber D1 n1)
    (DominoNumber D2 n2)
    (DominoNumber D2 n1)
    (DominoNumber D3 n3)
    (DominoNumber D3 n1)
    (DominoNumber D4 n1)
    (DominoNumber D4 n3)
    (DominoNumber D5 n4)
    (DominoNumber D5 n2)
    (DominoNumber D6 n5)
    (DominoNumber D6 n2)
    (Clear)
)

(:goal (and
            (Inserted D1)
            (Inserted D2)
            (Inserted D3)
            (Inserted D4)
            (Inserted D5)
            (Inserted D6)
        )
)
)