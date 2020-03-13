
osc1337:::nullpng()

barplot(1:10)

z <- capture.output(osc1337::osc1337())

#TODO: This can vary if running inside screen / tmux
z <- substring(z[4], 900, 999)
z <- sum(as.integer(charToRaw(z)))

stopifnot(identical(z, 8545L)) # Awful hash

