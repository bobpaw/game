.[] | {class: .class | rtrimstr("able") | ascii_downcase, type: .type | ascii_downcase | sub("one-handed"; "onehand"), name, power, id} | "\t\titem(\(.id), \(.class), \(.type), \"\(.name)\", \(.power))"
