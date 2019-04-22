function turn()
    sq = 0
    i = 0
    while(i < 100)
    do
        a, b, c, d, e, f, g = sqr_info(sq)
        if a == false and d == false then
            i = 100
            return sq, 0
        elseif a == false and e== false then
            i = 100
            return sq, 1
        elseif a == false and f== false then
            i = 100
            return sq, 2
        elseif a == false and g == false then
            i = 100
            return sq, 3
        elseif a== true then
            i = i + 1
            sq = (sq + 1)%100
        end
    end
end

function i_lose()
    n = get_opponent_name()
    return "But hey, at least I didn't crash the code. Good job ".. n .. "!\n"
    end

function i_win()
    n = get_opponent_name()
    return "Heyy, that's pretty good! Next time ".. n .. ".\n"
    end

function get_name()
    return "Lucy Oliverio"
end

