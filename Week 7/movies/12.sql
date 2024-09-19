SELECT DISTINCT
    movies.title
FROM
    movies
JOIN
    stars ON
    stars.movie_id = movies.id
JOIN
    people ON
    people.id = stars.person_id
WHERE
    movies.id IN(
        SELECT
            movie_id
        FROM
            stars
        WHERE
            person_id = (
                SELECT
                    id
                FROM
                    people
                WHERE
                    name = "Bradley Cooper"
                    )
             )
    AND
        movies.id IN(
            SELECT
                movie_id
            FROM
                stars
            WHERE
                person_id = (
                    SELECT
                        id
                    FROM
                        people
                    WHERE
                        name = "Jennifer Lawrence"
                        )
                    );
