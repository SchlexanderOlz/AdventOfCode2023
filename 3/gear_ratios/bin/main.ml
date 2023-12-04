let read_file filename = 
  let lines = ref [] in
  let chan = open_in filename in
    try
      while true; do
        lines := input_line chan :: !lines
      done; !lines
    with End_of_file ->
      close_in chan;
       List.rev !lines ;;

let find_adjecent lines =
  for i = 0 to Array.length lines do 
    lines.(i)
  done

let () = print_endline "Hello, World!"

