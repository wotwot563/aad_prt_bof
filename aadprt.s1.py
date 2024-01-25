from typing import List, Tuple

from outflank_stage1.task.base_bof_task import BaseBOFTask
from outflank_stage1.task.enums import BOFArgumentEncoding

class PsmBOF(BaseBOFTask):
    def __init__(self):
        super().__init__("aadprt", base_binary_name="aadprt")
        self.parser.description = "Request an Azure AD PRT."
        self.parser.add_argument("nonce", help="The PRT nonce, request from roadrecon auth --prt-init.")

    def _encode_arguments_bof(self, arguments: List[str]) -> List[Tuple[BOFArgumentEncoding, str]]:
        parser_arguments = self.parser.parse_args(arguments)
        return [(BOFArgumentEncoding.WSTR, parser_arguments.nonce)]
