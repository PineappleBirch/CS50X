-- Keep a log of any SQL queries you execute as you solve the mystery.
/*
The crime took place on the 28th of July 2023 (2023-07-28) at 10:15am on Humphrey Street.
Three witnesses point out Bakery.
Littering took place at 16:36 with no known witnesses.(whatever that means, lol)

Witnesses' clues:

    Ruth: "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."

    Eugene: "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM
on Leggett Street and saw the thief there withdrawing some money."

    Raymond: "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that
they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket."

Suspects:

    After Ruth's testimony:

    :name:
    Vanessa
    Bruce
    Barry
    Luca
    Sofia
    Iman
    Diana
    Kelsey

    After Eugene's testimony:

    :name:         :amount:
    Bruce        |  50
    Diana        |  35
    Iman         |  20
    Luca         |  48


    After Raymond's testimony:
    :thief:     |   :accomplice:
    Bruce       |   Robin
    Diana       |   Philip


Confirmed Thief, Accomplice, and Escape Location:

Thief:

    :name:
    Bruce

Accomplice:

    :name:
    Robin

Location of escape:

    :location:
    New York City

*/


-- Crime scene description
SELECT
    description
FROM
    crime_scene_reports
WHERE
    month = "7" AND
    day = 28 AND
    street = "Humphrey Street";

-- interviews transcript inspection
SELECT
    name, transcript
FROM
    interviews
WHERE
    year = 2023 AND
    month = 7 AND
    day = 28 AND
    transcript LIKE "%bakery%";

-- Ruth's lead - within 10 minutes after the robbery (10:15am - 10:25am) car left the parking lot
SELECT
    /*
    bakery_security_logs.activity,
    bakery_security_logs.license_plate,
    */
    people.name
FROM
    bakery_security_logs
JOIN
    people ON
    bakery_security_logs.license_plate = people.license_plate
WHERE
    year = 2023 AND
    month = 7 AND
    day = 28 AND
    hour = 10 AND
    minute >= 15 AND
    minute <= 25;

-- Eugene's lead - recognised the thief from earlier that day when the thief was withdrawing money from ATM on Leggett Street
SELECT
    people.name,
    atm_transactions.amount
FROM
    people
JOIN
    bank_accounts ON
    bank_accounts.person_id = people.id
JOIN
    atm_transactions ON
    atm_transactions.account_number = bank_accounts.account_number
WHERE
    people.name IN(
        'Vanessa', 'Bruce', 'Barry', 'Luca', 'Sofia', 'Iman', 'Diana', 'Kelsey'
    ) AND
    year = 2023 AND
    month = 7 AND
    day = 28 AND
    atm_location = 'Leggett Street' AND
    transaction_type = 'withdraw';

-- Raymond's lead - identiying the caller and receiver at time a little after the thief left the crime scene, call duration was less than 1 minute (60)
    -- Identifying the caller (thief suspects) and receiver (accomplice suspects)
SELECT
    caller.name AS caller_name,
    receiver.name AS receiver_name
FROM
    phone_calls
JOIN
    people AS caller ON
    phone_calls.caller = caller.phone_number
JOIN
    people AS receiver ON
    phone_calls.receiver = receiver.phone_number
WHERE
    caller.name IN(
        'Bruce','Diana','Iman','Luca'
    ) AND
    year = 2023 AND
    month = 7 AND
    day = 28 AND
    duration < 60;

-- Confirming the identity of the thief and accomplice and identifying the location of escape (city)
SELECT
    people.name,
    airports_2.city AS destination_city
FROM
    people
JOIN
    passengers ON
        passengers.passport_number = people.passport_number
JOIN
    flights ON
        flights.id = passengers.flight_id
JOIN
    airports AS airports_2 ON
        airports_2.id = flights.destination_airport_id
WHERE
    people.name IN (
        'Bruce',
        'Diana'
        ) AND
    flights.year = 2023 AND
    flights.month = 7 AND
    flights.day = 29 AND
    flights.origin_airport_id = (
        SELECT
            id
        FROM
            airports
        WHERE
            city = 'Fiftyville'
            )
ORDER BY
    flights.hour,
    flights.minute
LIMIT 1;

