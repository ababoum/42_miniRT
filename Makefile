all:
	@make -C mandatory

clean:
	@make clean -C mandatory
	@make clean -C bonus

fclean:
	@make fclean -C mandatory
	@make fclean -C bonus

bonus:
	@mkdir -p srcs_bonus
	@cp -rn srcs/* srcs_bonus
	@make -C bonus

bonus_clean:
	@rm -rf srcs_bonus
		
re:	fclean $(NAME)

.PHONY: clean fclean all re bonus bonus_clean