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


let sum_numbers (lines: string array) =
  let directions = [(-1, -1); (-1, 0); (0, -1); (1, 0); (0, 1); (1, 1); (-1, 1); (1, -1)] in
  
  let is_symbol ch =  
    let code = Char.code ch in
    (code < 0x30 || code > 0x39) && code != 0x2e
  in
  let is_valid (row, column) = row >= 0
                               && column >= 0 
                               && row < Array.length lines
                               && column < String.length lines.(0)
  in
  let rec get_number (row, col) sum (valid: bool ref) =
    let rec check_directions = function 
        | [] -> false
        | (drow, dcol) :: rest -> 
          if is_valid (row + drow, col + dcol) && is_symbol lines.(row + drow).[col + dcol] then true
          else check_directions rest
    in

    if is_valid (row, col) && (not (lines.(row).[col] = '.')) && (not (is_symbol lines.(row).[col])) then
      begin
        if (not !valid) && check_directions directions then
          valid := true;
        
        get_number (row, col + 1) (10 * sum + (int_of_char lines.(row).[col]) - 0x30) valid
      end
    else
      sum
  in

  let row_len = Array.length lines in
  let rec parse_row row row_sum =
    if row >= row_len then row_sum
    else
    let len = String.length lines.(0) in
    let rec parse current sum =
      if current >= len then sum
      else
        let valid = ref false in
        let number = get_number (row, current) 0 valid in
        let inc = 1 + int_of_float (floor (log10 (float_of_int number))) in
        if (not !valid) then 
            parse (current + inc) sum
        else 
            parse (current + inc) (sum + number)
    in
    parse_row (row + 1) (parse 0 row_sum)
  in

  parse_row 0 0


let () =  
  let sum = sum_numbers (Array.of_list (read_file "./input.txt")) in
  print_int sum;
;;

