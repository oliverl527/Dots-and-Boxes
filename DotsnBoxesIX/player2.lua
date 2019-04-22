sq = 0
ed = 2
function turn()
    a, b, c, d, e, f, g = sqr_info(sq)
    if sq == 100 then
        sq = 0
        ed = 0
        print("return: ", sq, ed)
        return sq, ed
    elseif ed == 4 then
        ed = 0
        sq = sq + 1
        print("return: ", (sq-1), 3)
        return (sq-1), 3
    else
    ed = ed + 1
    print("return: ", sq, (ed-1))
    return sq, (ed - 1)
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
    return "Comp Player"
end

