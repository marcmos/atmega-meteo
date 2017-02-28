import System.Serial
import System.IO (hPutChar)
import Data.Char (chr)
import Network.HTTP.Simple
import Data.Time.Clock
import Data.Time.Calendar
import Control.Concurrent

import Pollution

main :: IO ()
main = do
  serial <- openSerial "/dev/ttyACM0" B9600 8 One NoParity NoFlowControl
  threadDelay 1000000
  today <- utctDay <$> getCurrentTime
  pollution <- currentMeasurements . getResponseBody <$> fetchPollution today
  putStrLn $ show pollution
  hPutChar serial ' '
  hPutChar serial $ chr . round . snd $ pollution !! 0
  hPutChar serial $ chr . round . snd $ pollution !! 1
