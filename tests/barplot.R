
osc1337:::nullpng()

barplot(1:10)

z <- capture.output(osc1337:::autoshow())

#TODO: This can vary if running inside screen / tmux
z <- substring(z[4], 900, 999)
z <- sum(as.integer(charToRaw(z)))

print(z)
stopifnot(identical(z, 143L)) # Awful hash

